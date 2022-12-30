// Alessandro Pegoraro - Graphics Programming
// This file was taken and modified from the Chili Direct3D Engine. <http://www.planetchili.net>	

#include "Window.h"


////// Window Class Stuff //////


Window::WindowClass Window::WindowClass::_window_class;

Window::WindowClass::WindowClass() noexcept
	: _h_instance(GetModuleHandle(nullptr))
{
	WNDCLASSEX window_class = { 0 };

	window_class.cbSize         = sizeof(window_class);
	window_class.style          = CS_OWNDC;
	window_class.lpfnWndProc    = handleMsgSetup;
	window_class.cbClsExtra     = 0;
	window_class.cbWndExtra     = 0;
	window_class.hInstance      = getInstance();
	window_class.hIcon          = nullptr;
	window_class.hIconSm        = nullptr;
	window_class.hCursor        = nullptr;
	window_class.hbrBackground  = nullptr;
	window_class.lpszMenuName   = nullptr;
	window_class.lpszClassName  = getName();

	RegisterClassEx(&window_class);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(getName(), getInstance());
}

LPCSTR Window::WindowClass::getName() noexcept { return _window_class_name; }

HINSTANCE Window::WindowClass::getInstance() noexcept { return _window_class._h_instance; }



////// Window Stuff //////


Window::Window(int width, int height, LPCSTR name) noexcept
	: _width(width), _height(height)
{
	RECT window_rect;
	window_rect.left    = 100;
	window_rect.right   = _width + window_rect.left;
	window_rect.top     = 100;
	window_rect.bottom  = _height + window_rect.top;

	AdjustWindowRect(&window_rect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	_h_window = CreateWindowEx
	(
		0,
		WindowClass::getName(),
		name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		window_rect.right - window_rect.left, // width
		window_rect.bottom - window_rect.top, // height
		nullptr,
		nullptr,
		WindowClass::getInstance(),
		this // Custom creation param, will be useful to handle windows messages.
	);

	ShowWindow(_h_window, SW_SHOWDEFAULT);

	_renderer = std::make_unique<Renderer>(_h_window);
}

Window::~Window()
{
	DestroyWindow(_h_window);
}


void Window::setWindowName(LPCSTR new_name)
{
	SetWindowText(_h_window, new_name);
}


LRESULT WINAPI Window::handleMsgSetup(HWND h_window, UINT message_id, WPARAM w_parameter, LPARAM l_parameter) noexcept
{
	// Use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side.
	if (message_id == WM_NCCREATE)
	{
		// Extract ptr to window class from creation data.
		const CREATESTRUCTW* const creation_struct = reinterpret_cast<CREATESTRUCTW*>(l_parameter);
		Window* const window = static_cast<Window*>(creation_struct->lpCreateParams);

		// Set WinAPI-managed user data to store ptr to window class.
		SetWindowLongPtr(h_window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));

		// Set message procedure to normal (non-setup) handler, now that setup is finished.
		SetWindowLongPtr(h_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::handleMsgThunk));

		return window->handleMsg(h_window, message_id, w_parameter, l_parameter);
	}

	// If we get a message before the WM_NCCREATE message, handle with default handler.
	return DefWindowProc(h_window, message_id, w_parameter, l_parameter);
}

LRESULT WINAPI Window::handleMsgThunk(HWND h_window, UINT message_id, WPARAM w_parameter, LPARAM l_parameter) noexcept
{
	Window* const window = reinterpret_cast<Window*>(GetWindowLongPtr(h_window, GWLP_USERDATA));

	return window->handleMsg(h_window, message_id, w_parameter, l_parameter);
}

LRESULT Window::handleMsg(HWND h_window, UINT message_id, WPARAM w_parameter, LPARAM l_parameter) noexcept
{
	switch (message_id)
	{
	case WM_KILLFOCUS:
		keyboard.clearKeysStates();
		break;

	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
		keyboard.setKeyPressed(static_cast<unsigned char>(w_parameter));
		break;

	case WM_SYSKEYUP:
	case WM_KEYUP:
		keyboard.setKeyReleased(static_cast<unsigned char>(w_parameter));
		break;
		
	case WM_CLOSE:
		PostQuitMessage(0);

		// we don't want the DefProc to handle this message because
		// we want our destructor to destroy the window, so return 0 instead of break
		return 0;

	default: break;
	}

	return DefWindowProc(h_window, message_id, w_parameter, l_parameter);
}
