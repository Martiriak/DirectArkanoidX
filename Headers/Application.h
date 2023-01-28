// Alessandro Pegoraro - Graphics Programming

#pragma once

#include <vector>
#include <array>
#include <memory>
#include "Window.h"
#include "Drawables/Ball.h"
#include "Drawables/DestructibleBlock.h"
#include "Drawables/Paddle.h"


class Application
{
public:

	Window window;


	static constexpr int grid_dim_X = 8;
	static constexpr int grid_dim_Y = 10;


	Application() = delete;
	Application(int window_width, int window_height, LPCSTR window_name);

	void processFrame(double time_since_start, float delta_time);

private:

	std::vector<Drawable*> _drawables;
	std::array<std::array<std::unique_ptr<DestructibleBlock>, grid_dim_Y>, grid_dim_X> _blocks_grid;
	std::unique_ptr<Ball> _ball;
	std::unique_ptr<Paddle> _paddle;
};
