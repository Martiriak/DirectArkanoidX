// Alessandro Pegoraro - Graphics Programming

#include "Windows_Fixed.h"
#include "Window.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window window(800, 600, "Arkanoid X");

	// Get messages //

	MSG message;
	BOOL get_result;
	while ( (get_result = GetMessage(&message, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&message);
		
		DispatchMessage(&message);

		if (window.keyboard.isKeyPressed('F'))
		{
			window.setWindowName("Paganni Gianni");
		}

		if (window.keyboard.isKeyPressed('G'))
		{
			window.setWindowName("Gianni Paganni");
		}
	}

	return get_result == -1 ? -1 : message.wParam;
}
