/* FILE NAME: rndbase.c
 * PROGRAMMER: DS6
 * DATE: 17.06.2021
 * PURPOSE: 3D animation start up module.
 */
#include <windows.h>

#include "rnd.h"

VOID DS6_RndInit( HWND hWnd );

VOID DS6_RndClose( VOID );

VOID DS6_RndProjSet( VOID )
{
  DBL ratio.x, ratio.y;

  ratio_x = ratio_y = DS6_RndProjSize / 2;
  if (DS6_RndFrameW > DS6_RndFrameH)
    ratio_x *= (DBL)DS6_RndFrameW / DS6_RndFrameH;
  else
    ratio_y *= (DBL)DS6_RndFrameH / DS6_RndFrameW;
  DS6_RndMatrProj = 
    MatrFrustum(-ratio_x, ratio_x, -ratio_y, ratio_y, DS6_RndProjDist, DS6_RndProjFarClip);
  DS6RndMatrVP = MatrMulMatr(DS6_RndMatrView, DS6_RndMatrProj);
}
VOID DS6_RndResize( INT W, INT H )
{
  HDC hDC = GetDC(DS6_hRndWnd);

  if (DS6_hRndBmFrame != NULL)
    DeleteObject(DS6_hRndBmFrame);
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
  BitBlt(hDC, 0, 0, DS6_RndFrameW, DS6_RndFrameH,
    DS6_hRndDCFrame, 0, 0, SRCCOPY);
}

VOID DS6_RndStart( VOID );
VOID DS6_RndEnd( VOID );

VOID DS6_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, DS6_RndFrameW, DS6_RndFrameH, DS6_hDCRndFrame, 0, 0, SRCCOPY);
}

/* END OF 'rndbase.c' FILE */