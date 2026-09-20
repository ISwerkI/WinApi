#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>

#define IDC_STATIC 1000
#define IDC_EDIT 1001
#define IDC_BUTTON 1002

CONST CHAR g_szMyWindowClass[] = "My Window Class";
INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна;
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));
	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;


	//wClass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	//wClass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wClass.hIcon = (HICON)LoadImage
	(
		hInstance,"ethereum.ico", 
		IMAGE_ICON,LR_DEFAULTSIZE,
		LR_DEFAULTSIZE, LR_LOADFROMFILE
	);
	/*wClass.hIcon = (HICON)LoadImage
	(
		hInstance,"litecoin.ico", 
		IMAGE_ICON,LR_DEFAULTSIZE,
		LR_DEFAULTSIZE, LR_LOADFROMFILE
	);*/
	wClass.hIconSm = (HICON)LoadImage
	(
		hInstance,
		"litecoin.ico",
		IMAGE_ICON,
		LR_DEFAULTSIZE, LR_DEFAULTSIZE,
		LR_LOADFROMFILE
	);

	wClass.hCursor = (HCURSOR)LoadImage
	(
		hInstance, 
		"starcraft-original\\Working In Background.ani",
		IMAGE_CURSOR,
		32, 32,
		LR_LOADFROMFILE
		);
	//wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wClass.lpszClassName = g_szMyWindowClass;
	wClass.lpszMenuName = NULL;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.hInstance = hInstance;

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}

	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	int window_width = screen_width * 3 / 4;
	int window_height = screen_height * 3 / 4;
	int window_start_x = screen_width * 1 / 8;
	int window_start_y = screen_height * 1 / 8;

	//2) Создание окна;
	HWND hwnd = CreateWindowEx
	(
		NULL,				//exStyle
		g_szMyWindowClass,	//Class name
		g_szMyWindowClass,	//Window title
		WS_OVERLAPPEDWINDOW,//Window stytle
		window_start_x, window_start_y,	//Position
		window_width, window_height,	//Window size
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Class creation failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	//3) Запуск цикла сообщений;

	MSG msg;
	while (GetMessage(&msg, 0, 0, NULL) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hStatic = CreateWindowEx
		(
			NULL,
			"Static",
			"Этот static был создан при помощи функции CreateWindow()",
			WS_CHILD | WS_VISIBLE,
			10,10,
			500,25,
			hwnd,
			(HMENU)1000,
			GetModuleHandle(NULL),	//hInstance
			NULL
		);
		HWND hEdit = CreateWindowEx
		(
			NULL,
			"Edit",
			"Это текстовое поле создано при помощи функции CreateWindowEx()",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10,35,
			500, 25,
			hwnd,
			(HMENU)1001,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hButton = CreateWindowEx
		(
			NULL,
			"Button",
			"Применить",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			410, 67,
			100,32,
			hwnd,
			(HMENU)1002,
			GetModuleHandle(NULL),
			NULL
		);
	}
			break;

	case WM_SIZE:
		break;
	case WM_MOVE:
	{
		RECT window_rect;
		GetWindowRect(hwnd, &window_rect);
		INT width = window_rect.right - window_rect.left;
		INT height = window_rect.bottom - window_rect.top;
		CHAR sz_buffer[256] = {};
		sprintf
		(
			sz_buffer, 
			"%s, Size: %ix%i; Position: %ix%i;", 
			g_szMyWindowClass, 
			width, height,
			window_rect.left,window_rect.top
		);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);

	}
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 1002:
		{
			CHAR sz_buffer[256] = {};
			HWND hStatic = GetDlgItem(hwnd, 1000);
			HWND hEdit = GetDlgItem(hwnd, 1001);
			SendMessage(hEdit, WM_GETTEXT, 256, (LPARAM)sz_buffer);
			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			//SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		}

	}
			break;
	case WM_DESTROY:PostQuitMessage(0);		break;
	case WM_CLOSE:	DestroyWindow(hwnd);	break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}