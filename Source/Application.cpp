// Alessandro Pegoraro - Graphics Programming

#include "Application.h"
#include <string>


Application::Application(int window_width, int window_height, LPCSTR window_name)
	: window(window_width, window_height, window_name) { }


void Application::processFrame(float delta_time)
{
	window.getRenderer().clearBuffer(0.4f, 0.4f, 0.4f);

	window.getRenderer().tryStuff(delta_time);

	window.getRenderer().present();
}
