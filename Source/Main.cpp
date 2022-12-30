// Alessandro Pegoraro - Graphics Programming

#include "Windows_Fixed.h"
#include "Window.h"
#include <chrono>
#include <string>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window window(800, 600, "Arkanoid X");

	// Get messages //

	auto prev_frame = std::chrono::steady_clock::now();

	MSG message;
	bool running = true;
	while (running)
	{
		while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
			{
				running = false;
			}

			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		auto elapsed_time = std::chrono::steady_clock::now() - prev_frame;
		prev_frame = std::chrono::steady_clock::now();
		long long seconds_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count();

		if (window.keyboard.isKeyPressed(' '))
		{
			MessageBox(nullptr, std::to_string(seconds_elapsed).c_str(), "Delta Time", MB_OK);
		}
	}

	return message.wParam;
}
