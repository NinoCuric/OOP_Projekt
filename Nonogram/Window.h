#pragma once

#include <Windows.h>
#include "Nonogram.h"

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

	HWND GetGridButton(int row, int col) const;
	Nonogram* GetNonogram() const;
	int GetGridState(int index) const;
	void SetGridState(int index, int state);
	HBRUSH GetBrushForState(int state) const;
private:
	void CreateInitialButtons();
	void CreateResetButton();
	void CreateSubmitButtons();
	void ClearButtons();
	void CreateGrid(int size);
	void ClearGrid();

	HINSTANCE m_hInstance;
	HWND m_hWnd;
	HWND m_button1;
	HWND m_button2;
	HWND m_button3;
	HWND m_resetButton;
	HWND m_textBox;
	HWND m_submitButton;
	Nonogram* m_nonogram;
	std::vector<std::vector<HWND>> m_gridButtons;
	std::vector<int> m_playerState;
	HBRUSH m_emptyBrush;
	HBRUSH m_filledBrush;
};