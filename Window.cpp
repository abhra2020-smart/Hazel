#include "Window.h"

Window::Window()
{
}

void Window::onDestroy()
{
	b_isRunning = false;
	exit(0);
}

Window::~Window()
{
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		case WM_CREATE:
		{
			Window* window = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
			window->onCreate();
			break;
		}

		case WM_DESTROY:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onDestroy();
			::PostQuitMessage(0);
			break;
		}

		default: return ::DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return NULL;
}

bool Window::init(LPCWSTR title, int width, int height)
{
	WNDCLASSEX wnd;
	wnd.cbClsExtra = NULL;
	wnd.cbWndExtra = NULL;
	wnd.cbSize = sizeof(wnd);
	wnd.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wnd.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wnd.hInstance = NULL;
	wnd.lpszClassName = title;
	wnd.lpszMenuName = L"";
	wnd.lpfnWndProc = &WndProc;
	wnd.style = NULL;

	if (!::RegisterClassEx(&wnd)) return false;
	hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, title,
		             title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		             CW_USEDEFAULT, width, height, NULL, NULL, NULL,
		             this);

	if (!hwnd) return false;

	::ShowWindow(hwnd, SW_SHOW);
	::UpdateWindow(hwnd);

	b_isRunning = true;
	return true;
}

bool Window::broadcast()
{
	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	this->onUpdate();
	Sleep(0);

	return true;
}

bool Window::isRunning()
{
	return b_isRunning;
}

bool Window::release()
{
	if (!::DestroyWindow(hwnd)) return false;
	return true;
}
