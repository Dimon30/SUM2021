/* FILE NAME: rndprim.c
 * PROGRAMMER: DS6
 * DATE: 18.06.2021
 * PURPOSE: 3D animation primitive handle module.
 */

#include <stdio.h>
#include <string.h>
#include "../anim.h"

/* Primitive creation function.
 * ARGUMENTS:
 *   - primitive pointer:
 *       ds6PRIM *Pr;
 *   - vertex attributes array:
 *       ds6VERTEX *V;
 *   - number of vertices:
 *       INT NumOfV;
 *   - index array (for trimesh – by 3 ones, may be NULL)
 *       INT *I;
 *   - number of indices
 *       INT NumOfI;
 * RETURNS: None.
 */
VOID DS6_RndPrimCreate( ds6PRIM *Pr, ds6PRIM_TYPE Type, ds6VERTEX *V , INT NumOfV, INT *I, INT NumOfI )
{
  memset(Pr, 0, sizeof(ds6PRIM));
 
  if (V != NULL && NumOfV != 0)
  {
    glGenBuffers(1, &Pr->VBuf);
    glGenVertexArrays(1, &Pr->VA);

    glBindVertexArray(Pr->VA);
    glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ds6VERTEX) * NumOfV, V, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(ds6VERTEX), (VOID *)0);                                 /* position */

    glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(ds6VERTEX), (VOID *)sizeof(VEC));                       /* texture coordinates */

    glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(ds6VERTEX), (VOID *)(sizeof(VEC) + sizeof(VEC2)));      /* normal */

    glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(ds6VERTEX), (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2)));  /* color */

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glBindVertexArray(0);
  }

  if (I != NULL && NumOfI != 0)
  {
    glGenBuffers(1, &Pr->IBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NumOfI, I, GL_STATIC_DRAW);
    Pr->NumOfElements = NumOfI;
  }
  else
    Pr->NumOfElements = NumOfV;
  Pr->Trans = MatrIdentity();
} /* End of 'DS6_RndPrimCreate' function */



VOID DS6_RndPrimFree( ds6PRIM *Pr )
{

  glBindVertexArray(Pr->VA);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &Pr->VBuf);

  glBindVertexArray(0);
  glDeleteVertexArrays(1, &Pr->VA);

  glDeleteBuffers(1, &Pr->IBuf);


  memset(Pr, 0, sizeof(ds6PRIM));
}

VOID DS6_RndPrimDraw( ds6PRIM *Pr, MATR World )
{
  //MATR wvp;
  MATR
    w = MatrMulMatr(Pr->Trans, World),
    winv = MatrTranspose(MatrInverse(w)),
    wvp = MatrMulMatr(w, DS6_RndMatrVP);
  
  INT ProgId, loc;

  //wvp = MatrMulMatr3(Pr->Trans, World, DS6_RndMatrVP);

  glLoadMatrixf(wvp.A[0]);

  ProgId = DS6_RndMtlApply(Pr->MtlNo);

  /* Pass render uniforms */
  if ((loc = glGetUniformLocation(ProgId, "MatrWVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, wvp.A[0]);
  if ((loc = glGetUniformLocation(ProgId, "MatrW")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, w.A[0]);
  if ((loc = glGetUniformLocation(ProgId, "MatrWInv")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, winv.A[0]);
  if ((loc = glGetUniformLocation(ProgId, "CamLoc")) != -1) 
    glUniform3fv(loc, 1, &DS6_RndCamLoc.X);

  if (Pr->IBuf == 0)
  {
    glBindVertexArray(Pr->VA);
    glDrawArrays(GL_TRIANGLES, 0, Pr->NumOfElements);
    glBindVertexArray(0);
  }

  else
  {
    glBindVertexArray(Pr->VA);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);

    glDrawElements(GL_TRIANGLES, Pr->NumOfElements, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
}




/* Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       ds6PRIM *Pr;
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL DS6_RndPrimLoad( ds6PRIM *Pr, CHAR *FileName )
{
  FILE *F;
  INT i, nv = 0, nind = 0, size;
  ds6VERTEX *V;
  INT *Ind;
  static CHAR Buf[1000];

  memset(Pr, 0, sizeof(ds6PRIM));
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertexes and indexes */
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0;

      for (i = 1; Buf[i] != 0; i++)
        if (isspace((UCHAR)Buf[i - 1]) && !isspace((UCHAR)Buf[i]))
          n++;
      nind += (n - 2) * 3;
    }
  }

  size = sizeof(ds6VERTEX) * nv + sizeof(INT) * nind;
  if ((V = malloc(size)) == NULL)
    return FALSE;
  Ind = (INT *)(V + nv);
  memset(V, 0, size);

  /* Load primitive */
  rewind(F);
  nv = 0;
  nind = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;
      VEC4 c = {1, 1, 1, 1};

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      V[nv].C = c;
      V[nv++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0, n0, n1, nc;

      for (i = 1; Buf[i] != 0; i++)
        if (isspace((UCHAR)Buf[i - 1]) && !isspace((UCHAR)Buf[i]))
        {
          sscanf(Buf + i, "%i", &nc);
          if (nc < 0)
            nc = nv + nc;
          else
            nc--;

          if (n == 0)
            n0 = nc;
          else if (n == 1)
            n1 = nc;
          else
          {
            Ind[nind++] = n0;
            Ind[nind++] = n1;
            Ind[nind++] = nc;
            n1 = nc;
          }
          n++;
        }
    }
  }
  fclose(F);

  for (i = 0; i < nv; i++)
     V[i].N = VecSet(0, 0, 0);
  for (i = 0; i < nind; i += 3)
   {
     VEC
       p0 = V[Ind[i]].P,
       p1 = V[Ind[i + 1]].P,
       p2 = V[Ind[i + 2]].P,
       N = VecNormalize(VecCrossVec(VecSubVec(p1, p0), VecSubVec(p2, p0)));

     V[Ind[i]].N = VecAddVec(V[Ind[i]].N, N); /* VecAddVecEq(&V[Ind[i]].N, N); */
     V[Ind[i + 1]].N = VecAddVec(V[Ind[i + 1]].N, N);
     V[Ind[i + 2]].N = VecAddVec(V[Ind[i + 2]].N, N);
   }
  for (i = 0; i < nv; i++)
     V[i].N = VecNormalize(V[i].N);
  //nl = VecDotVec(V[i].N, L);
  //V[i].C = Vec4Set(200 * nl, 120 * nl, 100 * nl, 1);
  DS6_RndPrimCreate(Pr, DS6_RND_PRIM_TRIMESH, V, nv, Ind, nind);

  free(V);
  return TRUE;
} /* End of 'DS6_RndPrimLoad' function */

/* END OF 'rndprim.c' FILE */