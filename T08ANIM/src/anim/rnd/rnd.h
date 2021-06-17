/* FILE NAME: main.c
 * PROGRAMMER: DS6
 * DATE: 17.06.2021
 * PURPOSE: 3D animation start up module.
 */
#ifndef __rnd_h_
#define __rnd_h_

#include <windows.h>
#include "../../def.h"

extern HWND DS6_hRndWnd;                  /* Work window handle */
extern HDC DS6_hRndDCFrame;               /* Work window memory device context  */
extern HBITMAP DS6_hRndBmFrame;           /* Work window background bitmap handle */
extern INT DS6_RndFrameW, DS6_RndFrameH;  /* Work window size */

extern DBL
  DS6_RndProjSize,  /* Project plane fit square */
  DS6_RndProjDist ,  /* Distance to project plane from viewer (near) */
  DS6_RndProjFarClip;  /* Distance to project far clip plane (far) */

extern MATR
  DS6_RndMatrView, /* View coordinate system matrix */
  DS6_RndMatrProj, /* Projection coordinate system matrix */
  DS6_RndMatrVP;   /* Stored (View * Proj) matrix */



#endif /* __rnd_h_*/

/* END OF 'rnd.h' FILE */