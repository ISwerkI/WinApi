#include<Windows.h>

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

	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
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

	//2) Создание окна;
	HWND hwnd = CreateWindowEx
	(
		NULL,				//exStyle
		g_szMyWindowClass,	//Class name
		g_szMyWindowClass,	//Window title
		WS_OVERLAPPEDWINDOW,//Window stytle
		CW_USEDEFAULT,CW_USEDEFAULT,	//Position
		CW_USEDEFAULT,CW_USEDEFAULT	,	//Window size
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
			break;
	case WM_COMMAND:
			break;
	case WM_DESTROY:PostQuitMessage(0);		break;
	case WM_CLOSE:	DestroyWindow(hwnd);	break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}