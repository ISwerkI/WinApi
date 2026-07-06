#include <Windows.h>

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	MessageBox
	(
		NULL,															//- родительское окно
		"Hello WinAPI!",												//- сообщение, выводимое пользователю
		"Hello",														//- заголовок окна
		MB_YESNO | MB_HELP | MB_ICONERROR | MB_SYSTEMMODAL);			//- флаги, которые определяют значёк, выводимый в окне, набор кнопок, и некоторых
	
}