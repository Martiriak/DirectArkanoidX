// Alessandro Pegoraro - Graphics Programming

#include "Application.h"
#include <string>


Application::Application(int window_width, int window_height, LPCSTR window_name)
	: window(window_width, window_height, window_name) { }


void Application::processFrame(float delta_time)
{
	static constexpr float lerp_speed = 1.f;
	static bool is_reversed = false;
	static float elapsed_time = 0.f;
	static float red = 0.f;
	static float green = 1.f;
	static constexpr float blue = 0.f;

	if (window.keyboard.isKeyPressed(' '))
	{
		MessageBox(nullptr, std::to_string(delta_time).c_str(), "Delta Time", MB_OK);
	}

	if (!is_reversed)
	{
		if (elapsed_time > 1.f)
		{
			is_reversed = !is_reversed;
			elapsed_time = 1.f;
		}
	}
	else
	{
		if (elapsed_time < 0.f)
		{
			is_reversed = !is_reversed;
			elapsed_time = 0.f;
		}
	}

	red = elapsed_time;
	green = 1.f - elapsed_time;

	float increment = is_reversed ? -delta_time : delta_time;
	increment *= lerp_speed;

	elapsed_time += increment;

	window.getRenderer().clearBuffer(red, green, blue);

	window.getRenderer().tryStuff();

	window.getRenderer().present();
}
