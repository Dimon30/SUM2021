/* FILE NAME: rnddata.c
 * PROGRAMMER: DS6
 * DATE: 17.06.2021
 * PURPOSE: 3D animation start up module.
 */

#include <windows.h>
#include "rnd.h"

HWND DS6_hRndWnd;                  /* Work window handle */
HDC DS6_hRndDC;                    /* Work window memory device context  */
HGLRC DS6_hRndGLRC;                /* OpenGL rendering context */
INT DS6_RndFrameW, DS6_RndFrameH;  /* Work window size */

FLT
  DS6_RndProjSize = 0.1,  /* Project plane fit square */
  DS6_RndProjDist = 0.1,  /* Distance to project plane from viewer (near) */
  DS6_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */

MATR
  DS6_RndMatrView, /* View coordinate system matrix */
  DS6_RndMatrProj, /* Projection coordinate system matrix */
  DS6_RndMatrVP;   /* Stored (View * Proj) matrix */

VEC DS6_RndCamLoc;

/* END OF 'rnddata.c' FILE */