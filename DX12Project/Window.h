#pragma once

#include <windows.h>
#include <string>

class Window {
public:
	Window(std::wstring name, int width, int height);
	~Window();

	bool handleMessages();

private:
	HWND m_Handle;
	std::wstring m_Name;
	int m_Width;
	int m_Height;
};