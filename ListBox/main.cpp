#include <windows.h>
#include <stdio.h>
#include "resource.h"

CONST CHAR* g_sz_VALUES[] = { "This", "is", "my", "first", "List", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//DlgProc - это процедура окна, она обрабаьывает любые действия пользователя.
//Процедура окна - это самая обычная функция, которая неявно вызывается при запуске окна.

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST_BOX);
		for (int i = 0; i < sizeof(g_sz_VALUES) / sizeof(g_sz_VALUES[0]);i++)
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)g_sz_VALUES[i]);
	}
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK: 
		{
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST_BOX);
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			CHAR sz_buffer[256] = {};
			SendMessage(hListBox, LB_GETTEXT, i, (WPARAM)sz_buffer);
			CHAR sz_message[256] = {};
			sprintf(sz_message, "Вы выбрали вариант №%i со значением '%s'.", i, sz_buffer);
			MessageBox(hwnd, sz_message, "Выбранный элемент", MB_OK | MB_ICONINFORMATION);
		}
			break;
		case IDCANCEL: EndDialog(hwnd, 0);
		}
	}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}