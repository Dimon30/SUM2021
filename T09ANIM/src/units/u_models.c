#if 0
/*
 * FILE NAME: unit.c
 * PROGRAMMER: DS6
 * DATE: 19.06.2021
 * PURPOSE: implementation of animation object handling.
 */

#include <string.h>
#include "units.h"

typedef struct ds6

BOOL DS6_RndPrimsLoad( ds6PRIMS *Prs, CHAR *FileName )
{
  BYTE *mem, *ptr;
  INT flen;
  
  ptr = mem;
  if (Sign != *(DWORD *)"G3DM")
  {
    free(mem);
    fclose(F);
    return FALSE;
  }

  NumOfPrims = *(DWORD *)ptr;
  ptr += 4;
  NumOfMaterials = *(DWORD *)ptr;
  ptr += 4;
  NumOfTextures = *(DWORD *)ptr;
  ptr += 4;

  if (!DS6_RndPrimsCreate)


  free(mem);
  return TRUE;
}

/* END OF 'unit.c' FILE */
#endif