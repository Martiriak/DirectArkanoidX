// Alessandro Pegoraro - Graphics Programming
// This file was taken and modified from the Chili Direct3D Engine. <http://www.planetchili.net>	

#pragma once

#include "Windows_Fixed.h"


class Window
{
	// Singleton manages registration/cleanup of window class
	class WindowClass
	{
	public:

		static LPCSTR getName() noexcept;
		static HINSTANCE getInstance() noexcept;

	private:

		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;

		static constexpr LPCSTR _window_class_name = "DirectArkanoidX";
		static WindowClass _window_class;

		HINSTANCE _h_instance;
	};

public:

	Window(int width, int height, LPCSTR name) noexcept;
	~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

private:

	int _width;
	int _height;
	HWND _h_window;

	/**
	 * Used to initially setup the h_window to have a pointer to an instance of Window class,
	 * in its user data space.
	 */
	static LRESULT WINAPI handleMsgSetup(HWND h_window, UINT message_id, WPARAM w_parameter, LPARAM l_parameter) noexcept;

	/**
	 * Forwards the windows procedure to an instance of the Window class.
	 */
	static LRESULT WINAPI handleMsgThunk(HWND h_window, UINT message_id, WPARAM w_parameter, LPARAM l_parameter) noexcept;

	LRESULT handleMsg(HWND h_window, UINT message_id, WPARAM w_parameter, LPARAM l_parameter) noexcept;
};