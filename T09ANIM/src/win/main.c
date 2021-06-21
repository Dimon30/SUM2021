/* FILE NAME: main.c
 * PROGRAMMER: DS6
 * DATE: 17.06.2021
 * PURPOSE: 3D animation start up module.
 */

#include <windows.h>


#include "../def.h"

#include "../anim/rnd/rnd.h"

/* Window class name */
#define DS6_WND_CLASS_NAME "My Window Class Name"

/* Forward declaration */
LRESULT CALLBACK DS6_WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT CmdShow )
{
  HWND hWnd;
  MSG msg;
  WNDCLASS wc;
  
  SetDbgMemHooks();

  /* Fill window class structure */
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.hInstance = hInstance;
  wc.lpszClassName = DS6_WND_CLASS_NAME;
  wc.lpszMenuName = NULL;
  wc.lpfnWndProc = DS6_WinFunc;

  /* Register window class */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error regoister window class", "Error", MB_OK | MB_ICONERROR);
    return 0;
  }

  /* Window creation */
  hWnd = CreateWindow(DS6_WND_CLASS_NAME, "CGSG Primary Practice Group Animation System",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    NULL, NULL, hInstance, NULL);

  ShowWindow(hWnd, CmdShow);

/* Message loop */
  while (TRUE)
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      DispatchMessage(&msg);
    }
    else
      SendMessage(hWnd, WM_TIMER, 30, 0);

  return 30;
} /* End of 'WinMain' function */

/* Window handle function.
 * ARGUMENTS:
 *   - window handle:
 *      HWND hWnd;
 *   - message type (see WM_***):
 *      UINT Msg;
 *   - message 'word' parameter:
 *      WPARAM wParam;
 *   - message 'long' parameter:
 *      LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message depende return value.
 */
LRESULT CALLBACK DS6_WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  static INT w, h;
  static ds6PRIM Pr, PrP, PrS, PrF;

  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) + 2 * GetSystemMetrics(SM_CYBORDER);
    return 0;

  case WM_CREATE:
    SetTimer(hWnd, 30, 12, NULL);
    /*
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
    */
    DS6_AnimInit(hWnd);
    return 0;

  case WM_SIZE:
    /* Obtain new window width and height */
    /* DS6_RndResize(LOWORD(lParam), HIWORD(lParam)); */
    DS6_AnimResize(W, H);
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;

  case WM_TIMER:
    /*DS6_RndStart();
    \* scene rendaring *\
    Ellipse(DS6_hRndDCFrame, 5, 5, 100, 100);
    DS6_RndPrimDraw(&PrS, MatrIdentity());
    DS6_RndPrimDraw(&PrP, MatrIdentity());
    DS6_RndPrimDraw(&Pr, MatrIdentity());
    DS6_RndPrimDraw(&PrF, MatrScale(VecSet1(0.01)));
    DS6_RndEnd();
    */
    AnimRender();

    hDC = GetDC(hWnd);
    DS6_RndCopyFrame(hDC);
    /* InvalidateRect(hWnd, NULL, FALSE); */
    ReleaseDC(hWnd, hDC);
    return 0;

  case WM_PAINT:
    /*
    hDC = BeginPaint(hWnd, &ps);
    DS6_RndCopyFrame (hDC);;
    EndPaint(hWnd, &ps);
    */
    return 0;

  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    return 0;

  case WM_CLOSE:
    if(MessageBox(hWnd, "Are you sure to exit ?", "Exit", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON1) == IDYES)
      break;
    return 0;

  case WM_SYSKEYDOWN:
    break;

  case WM_MOUSEWHEEL:
    DS6_MouseWheel += (SHORT)HIWORD(wParam);
    return 0;

case WM_LBUTTONDOWN:
    SetCapture(hWnd);
    return 0;

  case WM_LBUTTONUP:
    ReleaseCapture();
    return 0;

  case WM_DESTROY:
    /*
    DS6_RndPrimFree(&PrF);
    DS6_RndPrimFree(&Pr);
    DS6_RndPrimFree(&PrS);
    DS6_RndPrimFree(&PrP);
    DS6_RndClose();
    KillTimer(hWnd, 30);
    */
    DS6_AnimClose();
    PostMessage(hWnd, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'WinFunc' function */

/* END OF 'main.c' FILE */