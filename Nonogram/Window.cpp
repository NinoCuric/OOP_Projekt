#include "Window.h"
#include <string>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static Window* pWindow = nullptr;

	if (uMsg == WM_CREATE)
	{
		pWindow = reinterpret_cast<Window*>(((LPCREATESTRUCT)lParam)->lpCreateParams);
	}
	
	switch (uMsg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hWnd, &ps);
		break;
	}
	case WM_COMMAND:
	{
		if (pWindow)
		{
			pWindow->HandleButtonClick(LOWORD(wParam));
		}
		break;
	}
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Window::HandleButtonClick(int buttonID)
{
	if (buttonID == 1 ||buttonID == 2 || buttonID == 3)
	{
		ClearButtons();
		CreateResetButton();
	}
	else if (buttonID == 4)
	{
		ClearButtons();
		CreateInitialButtons();
	}
}

Window::Window()
	: m_hInstance(GetModuleHandle(nullptr)), m_button1(nullptr), m_button2(nullptr), m_button3(nullptr), m_resetButton(nullptr), m_isInitialState(true)
{
	const wchar_t* CLASS_NAME = L"My Window Class";

	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpfnWndProc = WindowProc;

	RegisterClass(&wndClass);

	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	int width = 710;
	int height = 560;

	RECT rect;
	rect.left = 250;
	rect.top = 250;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	AdjustWindowRect(&rect, style, false);

	m_hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Nonogram",
		style,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		m_hInstance,
		this
	);

	CreateInitialButtons();

	ShowWindow(m_hWnd, SW_SHOW);
}

Window::~Window()
{
	const wchar_t* CLASS_NAME = L"My Window Class";
	UnregisterClass(CLASS_NAME, m_hInstance);
}

bool Window::ProcessMessages()
{
	MSG msg = {};

	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

void Window::CreateInitialButtons()
{
	m_button1 = CreateWindow(
		L"BUTTON",
		L"5 x 5",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		80, 350,
		150, 40,
		m_hWnd,
		(HMENU)1,
		m_hInstance,
		NULL
	);

	m_button2 = CreateWindow(
		L"BUTTON",
		L"10 x 10",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		280, 350,
		150, 40,
		m_hWnd,
		(HMENU)2,
		m_hInstance,
		NULL
	);

	m_button3 = CreateWindow(
		L"BUTTON",
		L"15 x 15",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		480, 350,
		150, 40,
		m_hWnd,
		(HMENU)3,
		m_hInstance,
		NULL
	);

	m_isInitialState = true;
}

void Window::CreateResetButton()
{
	m_resetButton = CreateWindow(
		L"BUTTON",
		L"Back",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		50, 50,
		50, 40,
		m_hWnd,
		(HMENU)4,
		m_hInstance,
		NULL
	);

	m_isInitialState = false;
}

void Window::ClearButtons()
{
	if (m_button1)
	{
		DestroyWindow(m_button1);
		m_button1 = nullptr;
	}
	if (m_button2)
	{
		DestroyWindow(m_button2);
		m_button2 = nullptr;
	}
	if (m_button3)
	{
		DestroyWindow(m_button3);
		m_button3 = nullptr;
	}
	if (m_resetButton)
	{
		DestroyWindow(m_resetButton);
		m_resetButton = nullptr;
	}

	InvalidateRect(m_hWnd, NULL, TRUE);
	UpdateWindow(m_hWnd);
}
