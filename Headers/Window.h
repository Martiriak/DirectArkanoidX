// Alessandro Pegoraro - Graphics Programming
// This file was taken and modified from the Chili Direct3D Engine. <http://www.planetchili.net>	

#pragma once

#include "Windows_Fixed.h"
#include <memory>
#include "ChiliException.h"
#include "Keyboard.h"
#include "Renderer.h"


class Window
{
//// INNER CLASSES ////
public:

	class Exception : public ChiliException
	{
	public:

		Exception(int line, const char* file, HRESULT h_result) noexcept;

		static std::string translateErrorCode(HRESULT h_result) noexcept;

		HRESULT getErrorCode() const noexcept;
		std::string getErrorString() const noexcept;

		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept override;

	private:

		HRESULT _h_result;
	};

private:

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

//// MEMBERS ////
public:

	Keyboard keyboard;

	Window(int width, int height, LPCSTR name) noexcept;
	~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	inline Renderer& getRenderer() { return *_renderer; }

	void setWindowName(LPCSTR new_name);

private:

	int _width;
	int _height;
	HWND _h_window;
	std::unique_ptr<Renderer> _renderer;

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


// Error exception helper macro.
#define MAKE_WINDOW_EXCEPTION(h_result) Window::Exception(__LINE__, __FILE__, h_result)
#define RETRIEVE_LAST_WINDOW_EXCEPTION() Window::Exception(__LINE__, __FILE__, GetLastError())
