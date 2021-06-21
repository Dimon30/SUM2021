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

  hDC = GetDC(hWnd);
  DS6_hRndDCFrame = CreateCompatibleDC(hDC);
  ReleaseDC(hWnd, hDC);

  DS6_RndProjSize = 0.1,
  DS6_RndProjDist = 0.1,
  DS6_RndProjFarClip = 300;

  DS6_RndFrameW = 47;
  DS6_RndFrameH = 47;
  DS6_hRndCamSet(VecSet(5, 5, 50), VecSet(0, 0, 0), VecSet(0, 1, 0));

}

VOID DS6_RndClose( VOID )
{
  if (DS6_hRndBmFrame != NULL)
    DeleteObject(DS6_hRndBmFrame);
  DeleteObject(DS6_hRndDCFrame);
}

VOID DS6_RndResize( INT W, INT H )
{
  HDC hDC;

  if (DS6_hRndBmFrame != NULL)
    DeleteObject(DS6_hRndBmFrame);

  hDC = GetDC(DS6_hRndWnd);
  DS6_hRndBmFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(DS6_hRndWnd, hDC);
  SelectObject(DS6_hRndDCFrame, DS6_hRndBmFrame);

  /* save size */
  DS6_RndFrameW = W;
  DS6_RndFrameH = H;

  /* recalculate projection */
  DS6_RndProjSet();
}



VOID DS6_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, DS6_RndFrameW, DS6_RndFrameH, DS6_hRndDCFrame, 0, 0, SRCCOPY);
}

VOID DS6_RndStart( VOID )
{
  SelectObject(DS6_hRndDCFrame,GetStockObject(NULL_PEN));
  SelectObject(DS6_hRndDCFrame,GetStockObject(DC_BRUSH));
  SetDCBrushColor(DS6_hRndDCFrame, RGB(40, 40, 40));
  Rectangle(DS6_hRndDCFrame, 0, 0, DS6_RndFrameW + 1, DS6_RndFrameH + 1);

  SelectObject(DS6_hRndDCFrame,GetStockObject(DC_PEN));
  SelectObject(DS6_hRndDCFrame,GetStockObject(NULL_BRUSH));
  SetDCPenColor(DS6_hRndDCFrame, RGB(2, 255, 225));

}
VOID DS6_RndEnd( VOID )
{
}

VOID DS6_RndProjSet( VOID )
{
  DBL rx, ry;

  rx = ry = DS6_RndProjSize / 2;
  if (DS6_RndFrameW > DS6_RndFrameH)
    rx *= (DBL)DS6_RndFrameW / DS6_RndFrameH;
  else
    ry *= (DBL)DS6_RndFrameH / DS6_RndFrameW;
  DS6_RndMatrProj = 
    MatrFrustum(-rx, rx, -ry, ry, DS6_RndProjDist, DS6_RndProjFarClip);
  DS6_RndMatrVP = MatrMulMatr(DS6_RndMatrView, DS6_RndMatrProj);
}
/* END OF 'rndbase.c' FILE */