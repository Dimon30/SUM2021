#include <windows.h>

#define WND_CLASS_NAME "Как хотите называйте"
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                              WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPreInstance, CHAR *CmdLine, INT ShowCmd)
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  /* Заполняем структуру класса окна */
  wc.style = 0;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  /* Регистрация класса в системе */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK | MB_ICONERROR);
    return 0;
  }
  /* Создание окна */
  hWnd =
    CreateWindow(WND_CLASS_NAME, 
      "Title",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT,
      NULL,
      NULL,
      hInstance,
      NULL);
  /* */
  ShowWindow(hWnd, ShowCmd);
  UpdateWindow(hWnd);
  /* Цикл обработки сообщений, пока не будет полученно сообщение 'WM_QUIT' */
  while (GetMessage(&msg, NULL, 0, 0))
    DispatchMessage(&msg);
  return msg.wParam;
}
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hDC;
  HPEN hPen, hPenOld;
  HBRUSH hBrush, hBrushOld;
  //LOGBRUSH  lb;
  //INT x, y;
  
  switch (Msg)
  {
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    
    hPen = CreatePen(PS_COSMETIC, 10, RGB(255, 100, 200));
    hPenOld = SelectObject(hDC, hPen);

    Rectangle(hDC, 30, 30, 60, 1000);
    Rectangle(hDC, 30, 30, 1600, 60);
    Rectangle(hDC, 30, 30, 60, 60);
    MoveToEx(hDC, 50, 50, NULL);
    LineTo(hDC, 600,700);
    Ellipse(hDC, 666, 665, 555, 555);

    SelectObject(hDC, hPenOld);
    DeleteObject(hPen);

    hBrush = CreateSolidBrush(RGB(255, 0, 0));
    hBrushOld = SelectObject(hDC, hBrush);

    Ellipse(hDC, 666, 665, 555, 555);

    SelectObject(hDC, hBrushOld);
    DeleteObject(hBrush);

    EndPaint(hWnd, &ps);
    return 0;
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}