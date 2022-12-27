// Alessandro Pegoraro - Graphics Programming

#include "Windows_Fixed.h"


LRESULT CALLBACK windowProcedure(HWND window, UINT message_id, WPARAM w_parameter, LPARAM l_parameter)
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


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const LPCSTR class_name = "DirectArkanoidX";

	// Register class //

	WNDCLASSEX window_class = {0};
	window_class.cbSize         = sizeof(window_class);
	window_class.style          = CS_OWNDC;
	window_class.lpfnWndProc    = windowProcedure;
	window_class.cbClsExtra     = 0;
	window_class.cbWndExtra     = 0;
	window_class.hInstance      = hInstance;
	window_class.hIcon          = nullptr;
	window_class.hCursor        = nullptr;
	window_class.hbrBackground  = nullptr;
	window_class.lpszMenuName   = nullptr;
	window_class.lpszClassName  = class_name;

	RegisterClassEx(&window_class);

	// Create window instance //

	HWND handle_window = CreateWindowEx
	(
		0,
		class_name,
		"Arkanoid X",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200,
		640, 480,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	ShowWindow(handle_window, SW_SHOW);

	// Get messages //

	MSG message;
	BOOL get_result;
	while ( (get_result = GetMessage(&message, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&message);

		DispatchMessage(&message);
	}

	return get_result == -1 ? -1 : message.wParam;
}
