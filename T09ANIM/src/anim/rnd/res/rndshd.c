/* FILE NAME: rndshd.c
 * PROGRAMMER: DS6
 * DATE: 23.06.2021
 * PURPOSE: 3D animation rendering shader handle functions module.
 */

#include "../rnd.h"

#include <stdio.h>
#include <string.h>


/***
 * Base shaders functions
 ***/

/* Load shader text from file function.
 * ARGUMENTS:
 *   - text file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (CHAR *) load text.
 */
CHAR * DS6_RndLoadTextFromFile( CHAR *FileName )
{
  FILE *F;
  INT flen;
  CHAR *txt;

  if ((F = fopen(FileName, "rb")) == NULL)
    return NULL;

  /* Measure file length */
  fseek(F, 0, SEEK_END);
  flen = ftell(F);
  rewind(F);

  /* Allocate memory */
  if ((txt = malloc(flen + 1)) == NULL)
  {
    fclose(F);
    return NULL;
  }
  /* Load text */
  memset(txt, 0, flen + 1);
  fread(txt, 1, flen, F);

  fclose(F);
  return txt;
} /* End of 'DS6_RndLoadTextFromFile' function */

/* Save log to file function.
 * ARGUMENTS:
 *   - shader prefix:
 *       CHAR *FileNamePrefix;
 *   - shader name:
 *       CHAR *ShaderName;
 *   - error text:
 *       CHAR *Text;
 * RETURNS: None.
 */
VOID DS6_RndShdLog( CHAR *FileNamePrefix, CHAR *ShaderName, CHAR *Text )
{
  FILE *F;

  if ((F = fopen("BIN/SHADERS/shd{30}DS6.log", "a")) == NULL)
    return;
  fprintf(F, "%s : %s\n%s\n\n", FileNamePrefix, ShaderName, Text);
  fclose(F);
} /* End of 'DS6_RndShdLog' function */


/* Load shader program function.
 * ARGUMENTS:
 *   - shader folder prefix (in 'BIN/SHADERS/***'):
 *       CHAR *FileNamePrefix;
 * RETUNS:
 *   (INT) load shader program Id.
 */
INT DS6_RndShdLoad( CHAR *FileNamePrefix )
{
  struct
  {
    CHAR *Name; /* Shader name (e.g. "VERT") */
    INT Type;   /* Shader type (e.g. GL_VERTEX_SHADER) */
    INT Id;     /* Obtained shader Id from OpenGL */
  } shd[] =
  {
    {"VERT", GL_VERTEX_SHADER, 0},
    {"FRAG", GL_FRAGMENT_SHADER, 0},
  };
  INT NoofS = sizeof(shd) / sizeof(shd[0]), i, prg = 0 , res;
  CHAR *txt;
  BOOL is_ok = TRUE;
  static CHAR Buf[1000];

  /* Load shader */
  for (i = 0; i < NoofS; i++)
  {
    /* Build shader name */
    sprintf(Buf, "BIN/SHADERS/%s/%s.GLSL", FileNamePrefix, shd[i].Name);

    /* Load shader text from file */
    txt = DS6_RndLoadTextFromFile(Buf);
    if (txt == NULL)
    {
      DS6_RndShdLog(FileNamePrefix, shd[i].Name, "Error load file");
      is_ok = FALSE;
      break;
    }

    /* Create shader */
    if ((shd[i].Id = glCreateShader(shd[i].Type)) == 0)
    {
      DS6_RndShdLog(FileNamePrefix, shd[i].Name, "Error create shader");
      is_ok = FALSE;
      break;
    }

    /* Attach text to shader */
    glShaderSource(shd[i].Id, 1, &txt, NULL);
    free(txt);

    /* Compile shader */
    glCompileShader(shd[i].Id);

    /* Handle errors */
    glGetShaderiv(shd[i].Id, GL_COMPILE_STATUS, &res);
    if (res != 1)
    {
      glGetShaderInfoLog(shd[i].Id, sizeof(Buf), &res, Buf);
      DS6_RndShdLog(FileNamePrefix, shd[i].Name, Buf);
      is_ok = FALSE;
      break;
    }
  }

  /* Create program */
  if (is_ok)
    if ((prg = glCreateProgram()) == 0)
    {
      DS6_RndShdLog(FileNamePrefix, "PROG", "Error create program");
      is_ok = FALSE;
    }
    else
    {
      /* Attach shaders to program */
      for (i = 0; i < NoofS; i++)
        if (shd[i].Id != 0)
          glAttachShader(prg, shd[i].Id);
      /* Link program */
      glLinkProgram(prg);
      glGetProgramiv(prg, GL_LINK_STATUS, &res);
      if (res != 1)
      {
        glGetProgramInfoLog(prg, sizeof(Buf), &res, Buf);
        DS6_RndShdLog(FileNamePrefix, "PROG", Buf);
        is_ok = FALSE;
      }
    }

  /* Handle errors */
  if (!is_ok)
  {
    /* Delete all shaders */
    for (i = 0; i < NoofS; i++)
      if (shd[i].Id != 0)
      {
        if (prg != 0)
          glDetachShader(prg, shd[i].Id);
        glDeleteShader(shd[i].Id);
      }
    /* Delete program */
    if (prg != 0)
      glDeleteProgram(prg);
    prg = 0;
  }
  return prg;
} /* End of 'DS6_RndShdLoad' function */

/* Delete shader program function.
 * ARGUMENTS:
 *   - shader program Id:
 *       INT ProgId;
 * RETUNS: None.
 */
VOID DS6_RndShdFree( INT ProgId )
{
  INT shds[5], n, i;

  if (ProgId == 0 || !glIsProgram(ProgId))
    return;
  glGetAttachedShaders(ProgId, 5, &n, shds);
  for (i = 0; i < n; i++)
    if (glIsShader(shds[i]))
    {
      glDetachShader(ProgId, shds[i]);
      glDeleteShader(shds[i]);
    }
    glDeleteProgram(ProgId);
} /* End of 'DS6_RndShdLoad' function */

/***
 * Shaders stock functions
 ***/


/* Shadre stock array and it size */

ds6SHADER DS6_RndShaders[DS6_STR_MAX];

/* Shader stock initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID DS6_RndShadersInit( VOID )
{
  //DS6_RndShadersSize = 0;
  DS6_RndShaderAdd("DEFAULT");
} /* End of 'DS6_RndShadersInit' function */

/* Shader stock deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID DS6_RndShadersClose( VOID )
{
  INT i;

  for (i = 0; i < DS6_RndShadersSize; i++)
    DS6_RndShdFree(DS6_RndShaders[i].ProgId);
  DS6_RndShadersSize = 0;
} /* End of 'DS6_RndShadersInit' function */

/* Shader add to stock function.
 * ARGUMENTS:
 *   - shader folder prefix:
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (INT) shader number in stock.
 */
INT DS6_RndShaderAdd( CHAR *FileNamePrefix )
{
  INT i;

  for (i = 0; i < DS6_RndShadersSize; i++)
    if (strcmp(FileNamePrefix, DS6_RndShaders[i].Name) == 0)
      return i;
  if (DS6_RndShadersSize >= DS6_STR_MAX)
    return 0;
  strncpy(DS6_RndShaders[DS6_RndShadersSize].Name, FileNamePrefix, DS6_STR_MAX - 1);
  DS6_RndShaders[DS6_RndShadersSize].ProgId = DS6_RndShdLoad(FileNamePrefix);
  return DS6_RndShadersSize++;
} /* End of 'DS6_RndShadersAdd' function */

/* Shader stock update function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID DS6_RndShadersUpdate( VOID )
{
  INT i;

  for (i = 0; i < DS6_RndShadersSize; i++)
  {
    DS6_RndShdFree(DS6_RndShaders[i].ProgId);
    DS6_RndShaders[i].ProgId = DS6_RndShdLoad(DS6_RndShaders[i].Name);
  }
} /* End of 'DS6_RndShadersUpdate' function */

/* END OF 'rndshd.c' FILE */