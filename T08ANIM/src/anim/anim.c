VOID DS6_AnimInit ( HWND hWnd )
{
  DS6_RndInit(hWnd);
  DS6_RndPrimCreate(&Pr, 3, 3);
  Pr.V[0].P = VecSet(0, 0, 0);
  Pr.V[1].P = VecSet(2, 0, 0);
  Pr.V[2].P = VecSet(0, 3, 0);
  Pr.I[0] = 0;
  Pr.I[1] = 1;
  Pr.I[2] = 2;

  DS6_RndPrimCreateSphere(&PrS, VecSet(0, 0, 0), 0.07, 27, 13);
  DS6_RndPrimCreatePlane(&PrP, VecSet(-8, 0, 8), VecSet(18, 0, 0), VecSet(0, 0, -18), 8, 8);
  DS6_RndPrimLoad(&PrF, "cow.obj");
}

VOID DS6_AnimClose ( VOID )
{
   DS6_RndPrimFree(&PrF);
    DS6_RndPrimFree(&Pr);
    DS6_RndPrimFree(&PrS);
    DS6_RndPrimFree(&PrP);
    DS6_RndClose();
}

VOID DS6_AnimResize(INT W, INT H)
{
  DS6_RndResize(LOWORD(lParam), HIWORD(lParam));
}

VOID DS6_AnimCopyFrame( HDC hDC )
{
  hDC = BeginPaint(hWnd, &ps);
  DS6_RndCopyFrame (hDC);;
  EndPaint(hWnd, &ps);
}

VOID DS6_AnimRender( VOID )
{
  /* scene rendering */
  DS6_RndStart();
  Ellipse(DS6_hRndDCFrame, 5, 5, 100, 100);
  DS6_RndPrimDraw(&PrS, MatrIdentity());
  DS6_RndPrimDraw(&PrP, MatrIdentity());
  DS6_RndPrimDraw(&Pr, MatrIdentity());
  DS6_RndPrimDraw(&PrF, MatrScale(VecSet1(0.01)));
  DS6_RndEnd();

  Response(Anim);
  Render(Anim);
}