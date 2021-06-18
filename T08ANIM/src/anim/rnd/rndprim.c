/* FILE NAME: rndprim.c
 * PROGRAMMER: DS6
 * DATE: 18.06.2021
 * PURPOSE: 3D animation primitive handle module.
 */

#include <string.h>
#include "rnd.h"

BOOL DS6_RndPrimCreate( ds6PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;

  memset(Pr, 0, sizeof(ds6PRIM));   /* <-- <string.h> */
  size = sizeof(ds6VERTEX) * NoofV + sizeof(INT) * NoofI;

  if ((Pr->V = malloc(size)) == NULL)
    return FALSE;
  Pr->I = (INT *)(Pr->V + NoofV);
  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;
  Pr->Trans = MatrIdentity();
  memset(Pr->V, 0, size);

  return TRUE;
}/*  End of 'RndPrimCreate' function */

VOID DS6_RndPrimFree( ds6PRIM *Pr )
{
  if (Pr->V != NULL)
    free(Pr->V);
  memset(Pr, 0, sizeof(ds6PRIM));
}

VOID DS6_RndPrimDraw( ds6PRIM *Pr, MATR World )
{
  INT i;
  
  MATR wvp = MatrMulMatr3(Pr->Trans, World, DS6_RndMatrVP);
  POINT *pnts;

  if ((pnts = malloc(sizeof(POINT) * Pr->NumOfV)) == NULL)
    return;

  /* Build projection */
  for (i = 0; i < Pr->NumOfV; i++)
  {
    VEC p = VecMulMatr(Pr->V[i].P, wvp);

    pnts[i].x = (INT)((p.X + 1) * DS6_RndFrameW / 2);
    pnts[i].y = (INT)((-p.Y + 1) * DS6_RndFrameH / 2);
  }

  /* Draw triangles */
  for (i = 0; i < Pr->NumOfI; i += 3)
  {
    MoveToEx(DS6_hRndDCFrame, pnts[Pr->I[i]].x, pnts[Pr->I[i]].y, NULL);
    LineTo(DS6_hRndDCFrame, pnts[Pr->I[i + 1]].x, pnts[Pr->I[i + 1]].y);
    LineTo(DS6_hRndDCFrame, pnts[Pr->I[i + 2]].x, pnts[Pr->I[i + 2]].y);
    LineTo(DS6_hRndDCFrame, pnts[Pr->I[i]].x, pnts[Pr->I[i]].y);
  }
  free(pnts);
}
/* END OF 'rndprim.c' FILE */