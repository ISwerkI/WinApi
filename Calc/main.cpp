#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "resource.h"
#include "dimentions.h"

CONST CHAR g_szClassName[] = "Calc P_418";
CONST CHAR* g_OPERATIONS[] = { "+","-","*","/" };
INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	/*wClass.hIcon = (HICON)LoadImage
	(
		hInstance, 
		"ico\\calc_calculator_10824.ico", 
		IMAGE_ICON, 
		LR_DEFAULTSIZE,
		LR_DEFAULTSIZE,
		LR_LOADFROMFILE);*/
	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.lpszClassName = NULL;
	wClass.lpszClassName = g_szClassName;

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}

	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_szClassName,
		g_szClassName,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,		//просто убрали WS_THICKFRAME грубо говоря (это рамки)
		CW_USEDEFAULT, CW_USEDEFAULT,
		WINDOW_SIZE_X, WINDOW_SIZE_Y,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
	
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hEdit = CreateWindowEx
		(
			NULL,
			"Edit",
			"0",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_NUMBER,
			g_i_START_X, g_i_START_Y,
			g_i_DISPLAY_WIDTH, g_i_DISPLAY_HEIGHT,
			hwnd,
			(HMENU)IDC_EDIT_DISPLAY,
			GetModuleHandle(NULL),	//hInstance
			NULL
		);
		CHAR sz_digit[2] = {};
		for (int i = 7; i > 0; i -= 3)
		{
			for (int j = 0; j < 3; j++)
			{
				sz_digit[0] = i + j + 48;
				CreateWindowEx
				(
					NULL,
					"Button",
					sz_digit,
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					//g_i_BUTTON_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL)*j,
					//g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL)*(2-i/3),
					BUTTON_SHIFT_X(j),BUTTON_SHIFT_Y(2-i/3),
					g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
					hwnd,
					(HMENU)(IDC_BUTTON_0+i+j),
					GetModuleHandle(NULL),
					NULL
				);
			}
		}
		CreateWindowEx
		(
			NULL,
			"Button",
			"0",
			WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			g_i_BUTTON_START_X,g_i_BUTTON_START_Y+(g_i_BUTTON_SIZE+g_i_INTERVAL)*3,
			g_i_BUTTON_DOUBLE_SIZE,g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_SHIFT_X(2), BUTTON_SHIFT_Y(3),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL),
			0
		);
		for (int i = 0; i < 4; i++)
		{
			CreateWindowEx
			(
				NULL,"Button",g_OPERATIONS[3-i],
				WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
				BUTTON_SHIFT_X(3),BUTTON_SHIFT_Y(i),
				g_i_BUTTON_SIZE,g_i_BUTTON_SIZE,
				hwnd,
				(HMENU)(IDC_BUTTON_PLUS + 3 - i),
				GetModuleHandle(NULL),
				0
			);
		}

		CreateWindowEx
		(
		NULL,"Button","<-",
		WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
		BUTTON_SHIFT_X(4),BUTTON_SHIFT_Y(0),
		g_i_BUTTON_SIZE,g_i_BUTTON_SIZE,
		hwnd,
		(HMENU)IDC_BUTTON_BSP,
		GetModuleHandle(NULL),
		0
		);

		CreateWindowEx
		(
			NULL,"Button","C",
			WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			BUTTON_SHIFT_X(4),BUTTON_SHIFT_Y(1),
			g_i_BUTTON_SIZE,g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_CLR,
			GetModuleHandle(0),
			0
		);

		CreateWindowEx
		(
			NULL,"Button","=",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_SHIFT_X(4),BUTTON_SHIFT_Y(2),
			g_i_BUTTON_SIZE,g_i_BUTTON_DOUBLE_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(0),
			0
		);

	}
	
	
		break;
	case WM_COMMAND:
	{
		CHAR sz_display[256] = {};
		CHAR sz_digit[2] = {};
		HWND hEditDisplay = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_POINT)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, 256, (LPARAM)sz_display);
			if (LOWORD(wParam) == IDC_BUTTON_POINT)
			{
				if (strchr(sz_display, '.'))break;
				strcat(sz_display, ".");
			}
			else
			{
				sz_digit[0] = LOWORD(wParam) - IDC_BUTTON_0 + 48;
				if (strcmp(sz_display, "0") == 0)strcpy(sz_display, sz_digit);
				else strcat(sz_display, sz_digit);
			}
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
	}
	break;
	case WM_KEYDOWN:
	{
		if (GetKeyState(VK_SHIFT) < 0 && wParam == 0x38)
		{
			if (wParam == 0x38)SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, TRUE, 0); break;
		}
		else if (wParam >= '0' && wParam <= '9')
			SendMessage(GetDlgItem(hwnd, wParam - '0' + IDC_BUTTON_0), BM_SETSTATE, TRUE, 0);
		else if(wParam >= 0x60 && wParam <=0x69)
			SendMessage(GetDlgItem(hwnd, wParam - 0x60 + IDC_BUTTON_0), BM_SETSTATE, TRUE, 0);
		switch (wParam)
		{
		case VK_OEM_PLUS:
		case VK_ADD:SendMessage(GetDlgItem(hwnd, IDC_BUTTON_PLUS), BM_SETSTATE, TRUE, 0); break;
		case VK_OEM_MINUS:
		case VK_SUBTRACT:SendMessage(GetDlgItem(hwnd, IDC_BUTTON_MINUS), BM_SETSTATE, TRUE, 0); break;
		case VK_OEM_PERIOD:SendMessage(GetDlgItem(hwnd, IDC_BUTTON_POINT), BM_SETSTATE, TRUE, 0); break;
		case VK_MULTIPLY:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, TRUE, 0); break;
		case VK_BACK: SendMessage(GetDlgItem(hwnd, IDC_BUTTON_BSP), BM_SETSTATE, TRUE, 0); break;
		case VK_ESCAPE: SendMessage(GetDlgItem(hwnd, IDC_BUTTON_CLR), BM_SETSTATE, TRUE, 0); break;
		case VK_RETURN: SendMessage(GetDlgItem(hwnd, IDC_BUTTON_EQUAL), BM_SETSTATE, TRUE, 0); break;
		case VK_OEM_2: SendMessage(GetDlgItem(hwnd, IDC_BUTTON_SLASH), BM_SETSTATE, TRUE, 0); break;
		}
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
	default:return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}