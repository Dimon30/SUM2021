

#include <windows.h>
#include <math.h>

#define WND_CLASS_NAME "ST"

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
VOID DrawHand( hDCFrame, INT x, INT y, DOUBLE a, INT W, INT L );
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd)
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, IDI_INFORMATION);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return 0;
  }
  hWnd = 
    CreateWindow(WND_CLASS_NAME,
      "T03CLOCK",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT,
      NULL,
      NULL,
      hInstance,
      NULL);

  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  INT size, i;
  INT cx, cy, n = 240, m = 160, p = 100, L, W;
  DOUBLE a, b, c, pi;
  HDC hDC;
  PAINTSTRUCT ps;
  SYSTEMTIME st;
  //HPEN hPen:
  static BITMAP bm;
  static HBITMAP hBmFrame, hBmImage;
  static HDC hDCFrame, hMemDCImage;
  static INT w, h;

  switch (Msg)
  {

  case WM_CREATE:

    SetTimer(hWnd, 30, 10, NULL);
    hBmFrame = NULL;
    hDC = GetDC(hWnd);
    hDCFrame = CreateCompatibleDC(hDC);
    hMemDCImage = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);

    /* load image */
    hBmImage = LoadImage(NULL, "CLOCK.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SelectObject(hMemDCImage, hBmImage);
    GetObject(hBmImage, sizeof(BITMAP), &bm);
    return 0;

  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    hDC = GetDC(hWnd);
    if (hBmFrame != NULL)
      DeleteObject(hBmFrame);
    hBmFrame = CreateCompatibleBitmap(hDC, w, h);
    ReleaseDC(hWnd, hDC);

    SelectObject(hDCFrame, hBmFrame);
    
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;

  case WM_TIMER:

    /* draw background */
    SelectObject(hDCFrame, GetStockObject(DC_PEN));
    SelectObject(hDCFrame, GetStockObject(DC_BRUSH));

    SetDCBrushColor(hDCFrame, RGB(200, 255, 255));
    Rectangle(hDCFrame, 0, 0, w + 1, h + 1);
    Rectangle(hDCFrame, 30, 30, 200, 200);

    /* draw clockface */
    size = w < h ? w : h;

    //BitBlt(hDCFrame, 0, 0, bm.bmWidth, bm.bmHeight, hMemDCImage, 0, 0, SRCCOPY);
    StretchBlt(hDCFrame, (w - size) / 2, (h - size) / 2, size, size, hMemDCImage, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

    /* draw hand */

      GetLocalTime( &st);
      pi = 3.14159265358979323846;
      a = (st.wSecond + st.wMilliseconds / 1000.0) * 2 * pi / 60;
      b = (st.wMinute + st.wSecond / 60.0) * 2 * pi / 60;
      c = (st.wHour + st.wMinute / 60.0) * 2 * pi / 12;
      cx = w / 2;
      cy = h / 2;
      //SelectObject(hDCFrame,GetStockObject(VIOLET_PEN));
      MoveToEx(hDCFrame, cx, cy, NULL);
      LineTo(hDCFrame, cx + (INT)(sin(a) * n), cy - (INT)(cos(a) * n));
      MoveToEx(hDCFrame, cx, cy, NULL);
      LineTo(hDCFrame, cx + (INT)(sin(b) * m), cy - (INT)(cos(b) * m));
      MoveToEx(hDCFrame, cx, cy, NULL);
      LineTo(hDCFrame, cx + (INT)(sin(c) * p), cy - (INT)(cos(c) * p));

      /* polygon */
      DrawHand(hDCFrame, cx + (INT)(sin(a) * n), cy - (INT)(cos(a) * n), a, L, w);
      

    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_ERASEBKGND:
    return 1;

  case WM_PAINT:


    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, w, h, hDCFrame, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;


  case WM_DESTROY:
    if (hBmFrame != NULL)
      DeleteObject(hBmFrame);
    DeleteDC(hDCFrame);
    KillTimer(hWnd, 30);
    PostQuitMessage(0);

    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
VOID DrawHand(hDCFrame, INT x, INT y, DOUBLE a, INT W, INT L)
{
  POINT pnts[] =
      {
        {cx + (INT)(sin(a) * L), cy - (INT)(cos(a) * L)}, 
        {cx + (INT)(sin(a) * w), cy - (INT)(cos(a) * w)},
        {cx + (INT)(sin(a) * (-w)), cy - (INT)(cos(a) * (-w))},
        {cx + (INT)(sin(a) * (-w)), cy - (INT)(cos(a) * (-w))},
        pnts1[sizeof(pnts) / sizeof(pts[0])];
      };
      s = sin(a);
      c = cos(a);
      for (i = 0; i < sizeof(pnts) / sizeof(pts[0]); i++)
      {
        pnts1[i].x = npnts[i].x * c + pnts[i].y * s;
        pnts1[i].y = npnts[i].y * c - pnts[i].x * s;
      }
      Polygon(hDC, pnts1, sizeof(pnts1) / sizeof pnts1[0]);
}
/*
POINT pnts[] =
{
  {cx + (INT)(sin(a) * L), cy - (INT)(cos(a) * L)}, 
  {cx + (INT)(sin(a) * w), cy - (INT)(cos(a) * w)},
  {cx + (INT)(sin(a) * (-w)), cy - (INT)(cos(a) * (-w))},
  {cx + (INT)(sin(a) * (-w)), cy - (INT)(cos(a) * (-w))},
  pnts1[sizeof(pnts) / sizeof(pts[0])];

Polygon(hDC, pnts, sizeof(pnts) / sizeof(pnts[0]));
*/