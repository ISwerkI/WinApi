#include <Windows.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, NULL);
};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:		
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK: MessageBox(hwnd, "Была нажата кнопка ОК!", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0);
		case IDC_BUTTON_COPY:
		{
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			CONST INT SIZE = 256;
			CHAR szBuffer[SIZE] = {};
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)szBuffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)szBuffer);
		}

		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}

