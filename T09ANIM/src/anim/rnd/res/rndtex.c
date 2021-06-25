#include "rndres.h"

INT DS6_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits )
{
  INT w = 0, h = 0;
  BYTE *mem;

  if (DS6_RndTexturesSize >= DS6_MAX_TEXTURES)
    return -1;

  glGenTextures(1, &DS6_RndTextures[DS6_RndTexturesSize].TexId);
  glBindTexture(GL_TEXTURE_2D, DS6_RndTextures[DS6_RndTexturesSize].TexId);
  if ((mem = malloc(w * h * 3)) != NULL)
  {
    INT n;

   //fread(mem, 3, w * h, F);

    //glBindTexture(GL_TEXTURE_2D, GL_TEXTURE_2D);
    /* glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_BGR,
         GL_UNSIGNED_BYTE, mem); */

    n = log(w > h ? w : h) / log(2);
    n = n < 1 ? 1 : n;

    glTexStorage2D(GL_TEXTURE_2D, n, GL_RGB8, w, h);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_BGR, GL_UNSIGNED_BYTE, mem);

    glGenerateMipmap(GL_TEXTURE_2D);

    free(mem);
  }


  return DS6_RndTexturesSize++;
}