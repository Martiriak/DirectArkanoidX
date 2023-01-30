// Alessandro Pegoraro - Graphics Programming

#include "Windows_Fixed.h"
#include "Application.h"
#include <chrono>


using chrono_clock = std::chrono::steady_clock;
using chrono_float = std::chrono::duration<float, std::chrono::seconds::period>;
using chrono_double = std::chrono::duration<double, std::chrono::seconds::period>;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	try
	{
		Application app(800, 800, "Arkanoid X");

		MessageBox(nullptr, "Press Space to start the game!\nPress A or D to move the paddle left or right.", "Controls", MB_OK | MB_ICONINFORMATION);

		const auto start_time = chrono_clock::now();
		auto prev_frame = start_time;

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
			auto total_elapsed_time = chrono_clock::now() - start_time;

			float seconds_elapsed = std::chrono::duration_cast<chrono_float>(elapsed_time).count();
			double seconds_since_start = std::chrono::duration_cast<chrono_double>(total_elapsed_time).count();

			app.processFrame(seconds_since_start, seconds_elapsed);
		}

		return message.wParam;
	}
	catch (const ChiliException& e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}

	return -1;
}
