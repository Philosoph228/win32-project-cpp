#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

const WCHAR szClassName[] = L"Win32Class_MainWindow";

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
    case WM_CREATE:
      return TRUE;
      break;

    case WM_PAINT:
      {
        PAINTSTRUCT ps{};
        HDC hdc;
        hdc = ::BeginPaint(hWnd, &ps);

        // Paint code goes here

        ::EndPaint(hWnd, &ps);
      }
      return 0;
      break;

    case WM_DESTROY:
      ::PostQuitMessage(0);
      return 0;
      break;
  }

  return ::DefWindowProc(hWnd, message, wParam, lParam);
}

BOOL InitInstance(HINSTANCE hInstance)
{
  WNDCLASSEX wcex{};
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = reinterpret_cast<WNDPROC> (WndProc);
  wcex.cbWndExtra = 0;  // Window data structure size goes here
  wcex.hInstance = hInstance;
  wcex.hIcon = ::LoadIcon(nullptr, IDI_APPLICATION);
  wcex.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = reinterpret_cast<HBRUSH> (COLOR_BTNFACE + 1);
  wcex.lpszMenuName = nullptr;
  wcex.lpszClassName = szClassName;

  return ::RegisterClassEx(&wcex);
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
  MSG msg{};

  InitInstance(hInstance);

  int screenWidth = ::GetSystemMetrics(SM_CXSCREEN);
  int screenHeight = ::GetSystemMetrics(SM_CYSCREEN);

  RECT rcClient{};
  rcClient.right = 640;
  rcClient.bottom = 480;
  ::AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, FALSE);

  const int windowWidth = rcClient.right - rcClient.left;
  const int windowHeight = rcClient.bottom - rcClient.top;

  const int x = (screenWidth - windowWidth) / 2;
  const int y = (screenHeight - windowHeight) / 2;

  const HWND hWindow = ::CreateWindowEx(0, szClassName, L"Sample Win32 project", WS_OVERLAPPEDWINDOW,
      x, y, windowWidth, windowHeight,
      nullptr, nullptr, hInstance, nullptr);
  ::ShowWindow(hWindow, nCmdShow);
  // Instantly call WM_PAINT to draw window contents
  ::UpdateWindow(hWindow);

  while (::GetMessage(&msg, nullptr, 0, 0))
  {
    ::TranslateMessage(&msg);
    ::DispatchMessage(&msg);
  }

  return static_cast<int> (msg.wParam);
}

