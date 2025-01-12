#include "Window.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static Window* pWindow = nullptr;

	if (uMsg == WM_CREATE)
	{
		pWindow = reinterpret_cast<Window*>(((LPCREATESTRUCT)lParam)->lpCreateParams);
	}

	switch (uMsg)
	{
	case WM_DRAWITEM: {
		LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;

		if (pDIS->CtlType == ODT_BUTTON) {		//if grid button
			HWND button = pDIS->hwndItem;

			if (pWindow) {								
				int buttonID = GetDlgCtrlID(button);
				int size = pWindow->GetNonogram()->GetSize();
				int index = buttonID - 1000;

				if (index >= 0 && index < size * size) {
					int state = pWindow->GetGridState(index);

					HBRUSH brush = (state == 1) ? pWindow->GetBrushForState(1) : pWindow->GetBrushForState(0);
					FillRect(pDIS->hDC, &pDIS->rcItem, brush);

					FrameRect(pDIS->hDC, &pDIS->rcItem, (HBRUSH)GetStockObject(BLACK_BRUSH));
					return TRUE;
				}
			}
		}
		break;
	}
	case WM_CTLCOLORBTN: {
		HDC hdc = (HDC)wParam;
		HWND button = (HWND)lParam;

		if (pWindow) {
			Nonogram* nonogram = pWindow->GetNonogram();
			if (!nonogram) break;

			int size = nonogram->GetSize();
			for (int row = 0; row < size; ++row) {
				for (int col = 0; col < size; ++col) {
					if (button == pWindow->GetGridButton(row, col)) {
						int index = row * size + col;
						int state = pWindow->GetGridState(index);

						SetBkColor(hdc, (state == 1) ? RGB(0, 0, 0) : RGB(255, 255, 255));
						return (LRESULT)pWindow->GetBrushForState(state);
					}
				}
			}
		}
		break;
	}
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
	if (buttonID == 1)
	{
		int size = 5;
		ClearButtons();
		CreateResetButton();
		CreateSubmitButtons();

		m_nonogram = new Nonogram(size, "");
		std::cout << "Nonogram created with size: " << size << std::endl;

		if (m_nonogram)
		{
			m_nonogram->Ispis();		///test
		}
	}
	else if (buttonID == 2)
	{
		int size = 10;
		ClearButtons();
		CreateResetButton();
		CreateSubmitButtons();

		m_nonogram = new Nonogram(size, "");
		std::cout << "Nonogram created with size: " << size << std::endl;

		if (m_nonogram)
		{
			m_nonogram->Ispis();		///test
		}
	}
	else if (buttonID == 3)
	{
		int size = 15;
		ClearButtons();
		CreateResetButton();
		CreateSubmitButtons();

		m_nonogram = new Nonogram(size, "");
		std::cout << "Nonogram created with size: " << size << std::endl;

		if (m_nonogram)
		{
			m_nonogram->Ispis();		///test
		}
	}
	else if (buttonID == 4)
	{
		ClearGrid();
		ClearButtons();
		CreateInitialButtons();

		if (m_nonogram)
		{
			delete m_nonogram;
			m_nonogram = nullptr;
		}
	}
	else if (buttonID == 5)
	{
		wchar_t text[256];
		GetWindowText(m_textBox, text, 256);

		std::wstring wstr(text);
		std::string kod(wstr.begin(), wstr.end());

		std::cout << "Nonogram updated with kod: " << kod << std::endl;
		m_nonogram->LoadFromCode(kod);

		SetWindowText(m_textBox, L"");

		if (m_nonogram) 
		{
			std::cout << "Creating Grid" << std::endl;
			CreateGrid(m_nonogram->GetSize());
		}
	}
	else if (buttonID >= 1000)
	{
		int index = buttonID - 1000;
		int state = GetGridState(index);

		SetGridState(index, (state == 1) ? 0 : 1);

		HWND button = m_gridButtons[index / m_nonogram->GetSize()][index % m_nonogram->GetSize()];
		InvalidateRect(button, NULL, TRUE);
	}
}

Window::Window()
	: m_hInstance(GetModuleHandle(nullptr)), m_button1(nullptr), m_button2(nullptr), m_button3(nullptr), m_resetButton(nullptr), m_nonogram(nullptr), m_textBox(nullptr), m_submitButton(nullptr), m_emptyBrush(nullptr), m_filledBrush(nullptr)
{
	m_emptyBrush = CreateSolidBrush(RGB(255, 255, 255));
	m_filledBrush = CreateSolidBrush(RGB(0, 0, 0));

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
	int height = 720;

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
	if (m_emptyBrush) DeleteObject(m_emptyBrush);
	if (m_filledBrush) DeleteObject(m_filledBrush);
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
}
void Window::CreateResetButton()
{
	m_resetButton = CreateWindow(
		L"BUTTON",
		L"Back",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		20, 20,
		50, 40,
		m_hWnd,
		(HMENU)4,
		m_hInstance,
		NULL
	);
}
void Window::CreateSubmitButtons() 
{
	m_textBox = CreateWindow(
		L"EDIT",
		L"",
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
		320, 30,
		200, 30,
		m_hWnd,
		NULL,
		m_hInstance,
		NULL
	);
	m_submitButton = CreateWindow(
		L"BUTTON",
		L"Submit",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		530, 30,
		80, 30,
		m_hWnd,
		(HMENU)5,
		m_hInstance,
		NULL
	);
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
	if (m_textBox)
	{
		DestroyWindow(m_textBox);
		m_textBox = nullptr;
	}
	if (m_submitButton)
	{
		DestroyWindow(m_submitButton);
		m_submitButton = nullptr;
	}

	if (m_nonogram)
	{
		delete m_nonogram;
		m_nonogram = nullptr;
	}

	InvalidateRect(m_hWnd, NULL, TRUE);
	UpdateWindow(m_hWnd);
}

void Window::CreateGrid(int size)
{
	ClearGrid();

	m_gridButtons.resize(size);
	m_playerState.resize(size * size, 0);

	const int buttonSize = 30;
	const int padding = 1;

	for (int row = 0; row < size; row++)
	{
		m_gridButtons[row].resize(size);
		for (int col = 0; col < size; col++)
		{
			m_gridButtons[row][col] = CreateWindow(
				L"BUTTON",
				L"",
				WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
				150 + col * (buttonSize + padding), 200 + row * (buttonSize + padding),
				buttonSize, buttonSize,
				m_hWnd,
				(HMENU)(1000 + row * size + col),
				m_hInstance,
				NULL
			);
		}
	}
}
void Window::ClearGrid()
{
	for (auto& row : m_gridButtons)
	{
		for (HWND button : row)
		{
			DestroyWindow(button);
		}
	}
	m_gridButtons.clear();
	m_playerState.clear();
}

HWND Window::GetGridButton(int row, int col) const
{
	if (row >= 0 && row < m_gridButtons.size() && col >= 0 && col < m_gridButtons[row].size())
	{
		return m_gridButtons[row][col];
	}
	return nullptr;
}

Nonogram* Window::GetNonogram() const
{
	return m_nonogram;
}

int Window::GetGridState(int index) const
{
	if (index >= 0 && index < m_playerState.size())
	{
		return m_playerState[index];
	}
	return -1;
}

void Window::SetGridState(int index, int state)
{
	if (index >= 0 && index < m_playerState.size())
	{
		m_playerState[index] = state;
	}
}

HBRUSH Window::GetBrushForState(int state) const
{
	return (state == 1) ? m_filledBrush : m_emptyBrush;
}