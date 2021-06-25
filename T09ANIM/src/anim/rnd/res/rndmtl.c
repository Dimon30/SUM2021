#include "rndres.h"

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
/* ***** */
  if ((loc = glGetUniformLocation(prg, "Ph")) != -1)
    glUniform1f(loc, mtl->Ph);

/* ***** */
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
  INT i;

  for (i = 0; i < DS6_RndMaterialsSize; i++)
    if (strcmp(Mtl, DS6_RndMaterials[i].Name) == 0)
      return i;
  if (DS6_RndShadersSize >= DS6_STR_MAX)
    return 0;
  //strncpy(DS6_RndMaterials[DS6_RndMaterialsSize].Name, FileNamePrefix, DS6_STR_MAX - 1);
  //DS6_RndMaterials[DS6_RndMaterialsSize].ProgId = DS6_RndShdLoad(FileNamePrefix);
  return DS6_RndMaterialsSize++;
}