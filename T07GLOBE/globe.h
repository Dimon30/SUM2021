/*
 * FILENAME: globe.h
 * PRAGRAMMER: DS6
 * DATE: 14.06.2021
 * PURPOSE:
 */

#ifndef __globe_h_
#define __globe_h_

#include <windows.h>

#pragma warning(disable: 4244)

/* Base float point type */
typedef DOUBLE DBL;

typedef struct tagVEC
{
  DBL X, Y, Z;
} VEC;

VOID GlobeSet( INT w, INT h, DBL R );
VOID GlobeDraw( HDC hDC );

/* VOID FlipFullScreen( HWND hWnd ); */

#endif /* __globe_h_ */
/* END of 'globe.h' */