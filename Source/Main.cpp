// Alessandro Pegoraro - Graphics Programming

#include "Windows_Fixed.h"
#include "Window.h"


LRESULT WINAPI windowProcedure(HWND window, UINT message_id, WPARAM w_parameter, LPARAM l_parameter)
{
	switch (message_id)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (w_parameter == 'F')
		{
			SetWindowText(window, "Gianni Paganni");
		}
		break;
	
	case WM_KEYUP:
		if (w_parameter == 'G')
		{
			SetWindowText(window, "Paganni Gianni");
		}
		break;

	default: break;
	}

	return DefWindowProc(window, message_id, w_parameter, l_parameter);
}


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
