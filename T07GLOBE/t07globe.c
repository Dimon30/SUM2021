/*
 * FILENAME: T07GLOBE
 * PRAGRAMMER: DS6
 * DATE: 14.06.2021
 * PURPOSE:
 */
#include <windows.h>
#include <math.h>
#include "globe.h"

#define WND_CLASS_NAME "SomeThing"
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
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
      "t07globe",
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
  HDC hDC;
  PAINTSTRUCT ps;
  static HBITMAP hBmFrame;
  static HDC hDCFrame;
  static INT w, h;

  switch (Msg)
  {

  case WM_CREATE:
    SetTimer(hWnd, 30, 10, NULL);
    hBmFrame = NULL;
    hDC = GetDC(hWnd);
    hDCFrame = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);


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

    GlobeSet(w / 2, h / 2, (w < h ? w : h) * 0.8);
    
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;

  case WM_TIMER:

    SelectObject(hDCFrame, GetStockObject(NULL_PEN));
    SelectObject(hDCFrame, GetStockObject(DC_BRUSH));

    SetDCBrushColor(hDCFrame, RGB(200, 255, 255));
    Rectangle(hDCFrame, 0, 0, w, h);

    GlobeDraw(hDC);

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