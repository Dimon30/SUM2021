/* FILE NAME: rndbase.c
 * PROGRAMMER: DS6
 * DATE: 17.06.2021
 * PURPOSE: 3D animation start up module.
 */

#include "rnd.h"


VOID DS6_hRndCamSet( VEC Loc, VEC At, VEC Up1 )
{
  DS6_RndMatrView = MatrView(Loc, At, Up1);
  DS6_RndMatrVP = MatrMulMatr(DS6_RndMatrView, DS6_RndMatrProj);
}

VOID DS6_RndInit( HWND hWnd )
{
  HDC hDC;

  DS6_hRndWnd = hWnd;
  DS6_hRndBmFrame = NULL;

 

  DS6_RndProjSize = 0.1,
  DS6_RndProjDist = 0.1,
  DS6_RndProjFarClip = 300;

  DS6_RndFrameW = 47;
  DS6_RndFrameH = 47;
  DS6_hRndCamSet(VecSet(5, 5, 50), VecSet(0, 0, 0), VecSet(0, 1, 0));

}

VOID DS6_RndClose( VOID )
{
}

VOID DS6_RndResize( INT W, INT H )
{
  SelectObject(DS6_hRndDCFrame, DS6_hRndBmFrame);

  /* save size */
  DS6_RndFrameW = W;
  DS6_RndFrameH = H;

  /* recalculate projection */
  DS6_RndProjSet();
}




VOID DS6_RndStart( VOID )
{

}
VOID DS6_RndEnd( VOID )
{
}

VOID DS6_RndProjSet( VOID )
{
  FLT rx, ry;

  rx = ry = DS6_RndProjSize / 2;
  if (DS6_RndFrameW > DS6_RndFrameH)
    rx *= (FLT)DS6_RndFrameW / DS6_RndFrameH;
  else
    ry *= (FLT)DS6_RndFrameH / DS6_RndFrameW;
  DS6_RndMatrProj = 
    MatrFrustum(-rx, rx, -ry, ry, DS6_RndProjDist, DS6_RndProjFarClip);
  DS6_RndMatrVP = MatrMulMatr(DS6_RndMatrView, DS6_RndMatrProj);
}
/* END OF 'rndbase.c' FILE */