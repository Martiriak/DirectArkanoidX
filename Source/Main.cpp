// Alessandro Pegoraro - Graphics Programming

#include "Windows_Fixed.h"
#include "Application.h"
#include <chrono>


using chrono_clock = std::chrono::steady_clock;
using chrono_float = std::chrono::duration<float, std::chrono::seconds::period>;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application app(800, 600, "Arkanoid X");

	auto prev_frame = chrono_clock::now();

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

		auto elapsed_time = chrono_clock::now() - prev_frame;
		prev_frame = chrono_clock::now();
		float seconds_elapsed = std::chrono::duration_cast<chrono_float>(elapsed_time).count();

		app.ProcessFrame(seconds_elapsed);
	}

	return message.wParam;
}
