#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <float.h>
#include<cstdio>
#include<iostream>
#include "resource.h"
#include "dimentions.h"
#include "ButtonsBMP.h"
#include "Skins.h"

CONST CHAR g_szClassName[] = "Calc P_418";
CONST CHAR* g_OPERATIONS[] = { "+","-","*","/" };
INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
VOID SetSkin(HWND hwnd, CONST CHAR sz_skin[]);

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
	static int index = 0;
	switch (uMsg)
	{
	case WM_CREATE:
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		//https://stackoverflow.com/questions/15543571/allocconsole-not-displaying-cout
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
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
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
		SendMessage
		(
			CreateWindowEx
			(
				NULL,
				"Button",
				"0",
				WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON | BS_BITMAP,
				g_i_BUTTON_START_X,g_i_BUTTON_START_Y+(g_i_BUTTON_SIZE+g_i_INTERVAL)*3,
				g_i_BUTTON_DOUBLE_SIZE,g_i_BUTTON_SIZE,
				hwnd,
				(HMENU)IDC_BUTTON_0,
				GetModuleHandle(NULL),
				NULL
			),
			BM_SETIMAGE,
			IMAGE_BITMAP,
			(LPARAM)(HBITMAP)LoadImage
			(
				GetModuleHandle(NULL),
				"BMP\\square_blue\\button_0.bmp",
				IMAGE_BITMAP,
				g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE,
				LR_LOADFROMFILE
			)
		);
		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
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
				WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON | BS_BITMAP,
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
		WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON | BS_BITMAP,
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
			WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON | BS_BITMAP,
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
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			BUTTON_SHIFT_X(4),BUTTON_SHIFT_Y(2),
			g_i_BUTTON_SIZE,g_i_BUTTON_DOUBLE_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(0),
			0
		);

	
	SetSkin(hwnd, "square_blue");
	AddFontResourceEx("Fonts\\digital-7 (mono).ttf", FR_PRIVATE, 0);
	HFONT hFront = CreateFont
	(
		g_i_FONT_HEIGHT,g_i_FONT_WIDTH,
		0,0,
		500,
		FALSE,FALSE,FALSE,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_CHARACTER_PRECIS,
		ANTIALIASED_QUALITY,
		DEFAULT_PITCH,
		"Digital-7 Mono"
	);
	SendMessage(hEdit, WM_SETFONT, (WPARAM)hFront, TRUE);
}
		break;
	case WM_CTLCOLOREDIT:
	{
		HDC hdc = (HDC)wParam;
		SetBkMode(hdc, OPAQUE);
		SetBkColor(hdc, g_DISPLAY_BACKGROUNG_COLOR[index]);
		HBRUSH hBrush = CreateSolidBrush(g_DISPLAY_FOREGROUND_COLOR[index]);
		SetTextColor(hdc, g_DISPLAY_FOREGROUND_COLOR[index]);

		HBRUSH hbrBackGround = CreateSolidBrush(g_WINDOW_BACKGROUNG_COLOR[index]);
		SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)hbrBackGround);
		SendMessage(hwnd, WM_ERASEBKGND, wParam, 0);

		return (LRESULT)hBrush;
	}
		break;
	case WM_COMMAND:
	{
		std::cout << LOWORD(wParam) << std::endl;
		static DOUBLE a = DBL_MIN;
		static DOUBLE b = DBL_MIN;
		static INT operation = 0;
		static BOOL input = FALSE;
		static BOOL input_operation = FALSE;
		CHAR sz_display[256] = {};
		CHAR sz_digit[2] = {};
		HWND hEditDisplay = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_POINT)
		{
			if (input_operation)
			{
				SendMessage(hEditDisplay, WM_SETTEXT,0, (LPARAM)"");
				input_operation = FALSE;
				input = TRUE;
			}
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
		if (LOWORD(wParam) == IDC_BUTTON_BSP)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, 256, (LPARAM)sz_display);
			int n = strlen(sz_display);
			if (n == 1)sz_display[0] = '0';
			else sz_display[strlen(sz_display) - 1] = 0;
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
		if (LOWORD(wParam) == IDC_BUTTON_CLR)
		{
			ZeroMemory(sz_digit, sizeof(sz_digit));
			ZeroMemory(sz_display, sizeof(sz_display));
			a = DBL_MIN;
			b = DBL_MIN;
			operation = 0;
			input = FALSE;
			input_operation = FALSE;
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"0");

		}
		if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam) <= IDC_BUTTON_SLASH)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, 256, (LPARAM)sz_display);
			if (a == DBL_MIN)a = atof(sz_display);
			else if (input) b = atof(sz_display);
			if(input)SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_EQUAL), 0);
			input = FALSE;
			operation = LOWORD(wParam);
			input_operation = TRUE;
		}
		if (LOWORD(wParam) == IDC_BUTTON_EQUAL)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, 256, (LPARAM)sz_display);
			if (a == DBL_MIN)a = atof(sz_display);
			else if(input) b = atof(sz_display);
			input = FALSE;
			switch (operation)
			{
			case IDC_BUTTON_PLUS:	a += b;	break;
			case IDC_BUTTON_MINUS:	a -= b;	break;
			case IDC_BUTTON_ASTER:	a *= b; break;
			case IDC_BUTTON_SLASH:	a /= b;	break;
			}
			input_operation = FALSE;
			sprintf(sz_display, "%g", a);
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
		SetFocus(hwnd);
	}
	
	break;
	case WM_KEYDOWN:
	{
		if (GetKeyState(VK_SHIFT) < 0 && wParam == 0x38)
		{
			//if (wParam == 0x38)
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, TRUE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_ASTER), 0);
			break;
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
		case VK_DIVIDE:SendMessage(GetDlgItem(hwnd, IDC_BUTTON_SLASH), BM_SETSTATE, TRUE, 0); break;
		}
	}
	break;
	case WM_KEYUP:
	{
		if (GetKeyState(VK_SHIFT) < 0 && wParam == 0x38)
		{
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, FALSE, 0); break;
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_ASTER), 0);
		}
		else if (wParam >= '0' && wParam <= '9')
		{
			SendMessage(GetDlgItem(hwnd, wParam - '0' + IDC_BUTTON_0), BM_SETSTATE, FALSE, 0);
			SendMessage(hwnd, WM_COMMAND, LOWORD(wParam - 48 + IDC_BUTTON_0), 0);
		}

		else if(wParam >= 0x60 && wParam <=0x69)
		{
			SendMessage(GetDlgItem(hwnd, wParam - 0x60 + IDC_BUTTON_0), BM_SETSTATE, FALSE, 0);
			SendMessage(hwnd, WM_COMMAND, LOWORD(wParam - 0x60 + IDC_BUTTON_0), 0);
		}
		switch (wParam)
		{
		case VK_OEM_PERIOD: 
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_POINT), BM_SETSTATE, FALSE, 0); 
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_POINT), 0); 
			break;
		case VK_MULTIPLY:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, FALSE, 0);
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_ASTER), 0); 
			break;
		case VK_OEM_PLUS:
		case VK_ADD:SendMessage(GetDlgItem(hwnd, IDC_BUTTON_PLUS), BM_SETSTATE, FALSE, 0);
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_PLUS), 0);
			break;
		case VK_OEM_MINUS:
		case VK_SUBTRACT:SendMessage(GetDlgItem(hwnd, IDC_BUTTON_MINUS), BM_SETSTATE, FALSE, 0); 
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_MINUS), 0);
			break;
		case VK_OEM_2:
		case VK_DIVIDE:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_SLASH), BM_SETSTATE, FALSE, 0);
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_SLASH), 0);
			break;
		case VK_BACK:		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_BSP), BM_SETSTATE, FALSE, 0); 
							SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_BSP), 0); break;
			break;
		case VK_ESCAPE:		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_CLR), BM_SETSTATE, FALSE, 0); 
							SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_CLR), 0); break;
			break;
		case VK_RETURN:		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_EQUAL), BM_SETSTATE, FALSE, 0); 
							SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_EQUAL), 0); 
			break;
		}
	}
	break;

	case WM_CONTEXTMENU:
	{
		//MessageBox(hwnd, "Вы нажали пкм", "WM_CONTEXTMENU", MB_OK | MB_ICONINFORMATION);
		HMENU hMenu = CreatePopupMenu();
		InsertMenu(hMenu, 0, MF_BYPOSITION | MF_STRING,IDR_EXIT, "Exit");
		InsertMenu(hMenu, 0, MF_BYPOSITION | MF_STRING,IDR_SQUARE_BLUE, "Square blue");
		InsertMenu(hMenu, 0, MF_BYPOSITION | MF_STRING,IDR_METAL_MISTRAL, "Metal mistral");
		InsertMenu(hMenu, 0, MF_BYPOSITION | MF_STRING,IDR_MINECRAFT_BUTTONS, "Minecraft glif");

		INT item = TrackPopupMenu(hMenu, TPM_BOTTOMALIGN | TPM_RETURNCMD | TPM_TOPALIGN | TPM_RETURNCMD | TPM_HORNEGANIMATION | TPM_VERPOSANIMATION,
			LOWORD(lParam), HIWORD(lParam),
			NULL,
			hwnd,
			NULL
		);
		switch (item)
		{
		//case IDR_METAL_MISTRAL: SetSkin(hwnd, "metal_mistral");		break;
		//case IDR_SQUARE_BLUE: SetSkin(hwnd, "square_blue");			break;
		//case IDR_MINECRAFT_BUTTONS: SetSkin(hwnd, "minecraft_buttons"); break;
		case IDR_EXIT: SendMessage(hwnd, WM_CLOSE, 0, 0);			break;
		}
		index = item - IDR_SQUARE_BLUE;
		SetSkin(hwnd, g_SKINS[index]);
		
		HWND hEditDisplay = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
		HDC hdcDisplay = GetDC(hEditDisplay);
		SendMessage(hwnd,WM_CTLCOLOREDIT,(WPARAM)hdcDisplay,0);
		ReleaseDC(hEditDisplay, hdcDisplay);
		SetFocus(hEditDisplay);
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

VOID SetSkin(HWND hwnd, CONST CHAR sz_skin[])
{
	CHAR sz_bitmap[256] = {};
	for (int i = 0; i <= 17; i++)
	{
		sprintf(sz_bitmap, "BMP\\%s\\%s", sz_skin, g_ButtonsBMP[i]);
		HBITMAP hBitmap = (HBITMAP)LoadImage
		(
			GetModuleHandle(NULL),
			//"BMP\\%s\\button_%i.bmp",
			sz_bitmap,
			IMAGE_BITMAP,
			i>0?g_i_BUTTON_SIZE:g_i_BUTTON_DOUBLE_SIZE, 
			i==17?g_i_BUTTON_DOUBLE_SIZE:g_i_BUTTON_SIZE,
			LR_LOADFROMFILE
		);
		std::cout << "SetSkin:\t";
		std::cout << GetLastError() << std::endl;
		std::cout << "\n---------------------------------------------\n" << std::endl;
		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_0 + i), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
	}
	/*for (int i = 0; i < 10; i++)
	{
		sprintf(sz_bitmap, "BMP\\%s\\button_%i.bmp", sz_skin, i);
		HBITMAP hBitmap = (HBITMAP)LoadImage
		(
			GetModuleHandle(NULL),
			//"BMP\\%s\\button_%i.bmp",
			sz_bitmap,
			IMAGE_BITMAP,
			i>0?g_i_BUTTON_SIZE:g_i_BUTTON_DOUBLE_SIZE, 
			g_i_BUTTON_SIZE,
			LR_LOADFROMFILE
		);
		std::cout << "SetSkin:\t";
		std::cout << GetLastError() << std::endl;
		std::cout << "\n---------------------------------------------\n" << std::endl;
		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_0 + i), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
		}
	*/
}