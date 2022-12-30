// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Window.h"


class Application
{
public:

	Window window;

	Application() = delete;
	Application(int window_width, int window_height, LPCSTR window_name);

	void processFrame(float delta_time);

private:
	

};
