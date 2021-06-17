/* FILE NAME: rnddata.c
 * PROGRAMMER: DS6
 * DATE: 17.06.2021
 * PURPOSE: 3D animation start up module.
 */

#include <windows.h>
#include "rnd.h"

HWND DS6_hRndWnd;                  /* Work window handle */
HDC DS6_hRndDCFrame;               /* Work window memory device context  */
HBITMAP DS6_hRndBmFrame;           /* Work window background bitmap handle */
INT DS6_RndFrameW, DS6_RndFrameH;  /* Work window size */

DBL
  DS6_RndProjSize = 0.1,  /* Project plane fit square */
  DS6_RndProjDist = 0.1,  /* Distance to project plane from viewer (near) */
  DS6_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */

MATR
  DS6_RndMatrView, /* View coordinate system matrix */
  DS6_RndMatrProj, /* Projection coordinate system matrix */
  DS6_RndMatrVP;   /* Stored (View * Proj) matrix */

/* END OF 'rnddata.c' FILE */