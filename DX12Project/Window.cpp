#include "Window.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

Window::Window(std::wstring name, int width, int height)
	: m_Handle(0)
	, m_Name(name)
	, m_Width(width)
	, m_Height(height)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = name.c_str();
	RegisterClass(&wc);

	m_Handle = CreateWindow(
		name.c_str(), name.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		0, 0, hInstance, 0
	);

	ShowWindow(m_Handle, SW_SHOWNORMAL);
	//UpdateWindow(hwnd);
}

Window::~Window()
{
	DestroyWindow(m_Handle);
	handleMessages();
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

bool Window::handleMessages()
{
	MSG msg;
	msg.message = NULL;
	bool quit = false;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (WM_CLOSE == msg.message || WM_QUIT == msg.message)
			quit = true;
	}

	return quit;
}