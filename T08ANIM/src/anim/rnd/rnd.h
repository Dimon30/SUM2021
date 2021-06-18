/* FILE NAME: main.c
 * PROGRAMMER: DS6
 * DATE: 17.06.2021
 * PURPOSE: 3D animation start up module.
 */
#ifndef __rnd_h_
#define __rnd_h_

#include "../../def.h"

extern HWND DS6_hRndWnd;                  /* Work window handle */
extern HDC DS6_hRndDCFrame;               /* Work window memory device context  */
extern HBITMAP DS6_hRndBmFrame;           /* Work window background bitmap handle */
extern INT DS6_RndFrameW, DS6_RndFrameH;  /* Work window size */

extern DBL
  DS6_RndProjSize,     /* Project plane fit square */
  DS6_RndProjDist ,    /* Distance to project plane from viewer (near) */
  DS6_RndProjFarClip;  /* Distance to project far clip plane (far) */

extern MATR
  DS6_RndMatrView, /* View coordinate system matrix */
  DS6_RndMatrProj, /* Projection coordinate system matrix */
  DS6_RndMatrVP;   /* Stored (View * Proj) matrix */

VOID DS6_RndInit( HWND hWnd );

VOID DS6_RndClose( VOID );

VOID DS6_RndProjSet( VOID );

VOID DS6_RndResize( INT W, INT H );

VOID DS6_RndStart( VOID );

VOID DS6_RndEnd( VOID );

VOID DS6_RndCopyFrame( HDC hDC );

VOID DS6_RndCamSet( VEC Loc, VEC At, VEC Up1 );

typedef struct tagds6VERTEX
{
  VEC P; /* Vertex position */
}ds6VERTEX;

typedef struct tagds6PRIM
{
  ds6VERTEX *V;
  INT NumOfV;
  INT *I;
  INT NumOfI;
  MATR Trans;
} ds6PRIM;

BOOL DS6_RndPrimCreate( ds6PRIM *Pr, INT NoofV, INT NoofI );

VOID DS6_RndPrimFree( ds6PRIM *Pr );

VOID DS6_RndPrimDraw( ds6PRIM *Pr, MATR World );

#endif /* __rnd_h_*/

/* END OF 'rnd.h' FILE */