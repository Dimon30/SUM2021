#include <string.h>

#include "../rnd.h"

ds6TEXTURE DS6_RndTextures[DS6_MAX_TEXTURES]; /* Array of textures */
INT DS6_RndTexturesSize;

VOID DS6_RndTexInit( VOID )
{
  DS6_RndTexturesSize = 0;
}

VOID DS6_RndTexClose( VOID )
{
  INT i;

  for (i = 0; i < DS6_RndTexturesSize; i++)
    glDeleteTextures(1, &DS6_RndTextures[i].TexId);
  DS6_RndTexturesSize = 0;
}

INT DS6_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits )
{
  INT n;

  if (DS6_RndTexturesSize >= DS6_MAX_TEXTURES)
    return -1;

  strcpy(DS6_RndTextures[DS6_RndTexturesSize].Name, Name);
  glGenTextures(1, &DS6_RndTextures[DS6_RndTexturesSize].TexId);
  glBindTexture(GL_TEXTURE_2D, DS6_RndTextures[DS6_RndTexturesSize].TexId);

  n = log(W > H ? W : H) / log(2);
  n = n < 1 ? 1 : n;

  glTexStorage2D(GL_TEXTURE_2D, n, GL_RGB8, W, H);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, W, H, GL_BGR, GL_UNSIGNED_BYTE, Bits);

  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  return DS6_RndTexturesSize++;
}