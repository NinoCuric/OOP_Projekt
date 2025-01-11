#pragma once

#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
public:
	Window();
	Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;
	~Window();

	bool ProcessMessages();

	void HandleButtonClick(int buttonID);
private:
	void CreateInitialButtons();
	void CreateResetButton();
	void ClearButtons();

	HINSTANCE m_hInstance;
	HWND m_hWnd;
	HWND m_button1;
	HWND m_button2;
	HWND m_button3;
	HWND m_resetButton;
	bool m_isInitialState;
};
