#include "../../anim.h"

ds6MATERIAL DS6_RndMaterials[DS6_MAX_MATERIALS]; /* Array of materials */
INT DS6_RndMaterialsSize;

VOID DS6_RndMtlInit( VOID )
{
  INT i;
  ds6MATERIAL mtl = {{0}};

  DS6_RndMaterialsSize = 0;

  strcpy(mtl.Name, "DEFAULT");
  mtl.Ka = VecSet1(0.1);
  mtl.Kd = VecSet1(1);
  mtl.Ks = VecSet1(0.0);
  mtl.Ph = 30;
  mtl.Trans = 1;
  mtl.ShdNo = 0;
  for (i = 0; i < 8; i++)
    mtl.Tex[i] = -1;

  DS6_RndMtlAdd(&mtl);
}

VOID DS6_RndMtlClose( VOID )
{
  DS6_RndMaterialsSize = 0;
}

INT DS6_RndMtlApply( INT MtlNo )
{
  INT prg, loc, i;
  ds6MATERIAL *mtl;

  /* Set material pointer */
  if (MtlNo < 0 || MtlNo >= DS6_RndMaterialsSize)
    MtlNo = 0;
  mtl = &DS6_RndMaterials[MtlNo];

  /* Set shader program Id */
  prg = mtl->ShdNo;
  if (prg < 0 || prg >= DS6_RndShadersSize)
    prg = 0;
  prg = DS6_RndShaders[prg].ProgId;

  glUseProgram(prg);
  /* Set shading parameters */
  if ((loc = glGetUniformLocation(prg, "Time")) != -1)
    glUniform1f(loc, DS6_Anim.Time);
  if ((loc = glGetUniformLocation(prg, "GlobalTime")) != -1)
    glUniform1f(loc, DS6_Anim.GlobalTime);
  if ((loc = glGetUniformLocation(prg, "Ka")) != -1)
    glUniform3fv(loc, 1, &mtl->Ka.X);
  if ((loc = glGetUniformLocation(prg, "Kd")) != -1)
    glUniform3fv(loc, 1, &mtl->Kd.X);
  if ((loc = glGetUniformLocation(prg, "Ks")) != -1)
    glUniform3fv(loc, 1, &mtl->Ks.X);
  if ((loc = glGetUniformLocation(prg, "Ph")) != -1)
    glUniform1f(loc, mtl->Ph);

  /* Set textures */
  for (i = 0; i < 8; i++)
  {
    CHAR tname[] = "IsTexture0"; /* --> shader: uniform bool IsTexture2; */

    tname[9] = '0' + i;
    if (mtl->Tex[i] != -1)
    {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, DS6_RndTextures[mtl->Tex[i]].TexId);
    }
    if ((loc = glGetUniformLocation(prg, tname)) != -1)
      glUniform1i(loc, mtl->Tex[i] != -1);
  }
  return prg;
} /* End of 'DS6_RndMtlApply' function */

INT DS6_RndMtlAdd( ds6MATERIAL *Mtl )
{
  if (DS6_RndMaterialsSize >= DS6_STR_MAX)
    return -1;
  DS6_RndMaterials[DS6_RndMaterialsSize] = *Mtl;
  return DS6_RndMaterialsSize++;
}