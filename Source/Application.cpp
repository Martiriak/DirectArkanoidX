// Alessandro Pegoraro - Graphics Programming

#include "Application.h"
#include <string>


Application::Application(int window_width, int window_height, LPCSTR window_name)
	: window(window_width, window_height, window_name) { }


void Application::processFrame(float delta_time)
{
	if (window.keyboard.isKeyPressed(' '))
	{
		MessageBox(nullptr, std::to_string(delta_time).c_str(), "Delta Time", MB_OK);
	}

	window.getRenderer().clearBuffer(0.2f, 0.6f, 0.2f);

	window.getRenderer().present();
}
