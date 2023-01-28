// Alessandro Pegoraro - Graphics Programming

#include "Application.h"
#include <string>
#include "Color.h"


Application::Application(int window_width, int window_height, LPCSTR window_name)
	: window(window_width, window_height, window_name)
{
	const float blocks_height = 0.1f;
	const float blocks_width = 0.3f;
	const Vector2 base_point = { -1.f + blocks_width * 0.5f, 1.f - blocks_height * 0.5f };
	const float offset_x = (2.f - blocks_width) / (grid_dim_X - 1);
	const float offset_y = blocks_height;

	for (int x = 0; x < _blocks_grid.size(); ++x)
		for (int y = 0; y < _blocks_grid[x].size(); ++y)
		{
			_blocks_grid[x][y] = std::make_unique<DestructibleBlock>
			(
				window.getRenderer(),
				base_point + Vector2{ offset_x * x, -offset_y * y },
				blocks_width,
				blocks_height,
				Color{255, 255, 255, 255}
			);
		}

	_ball = std::make_unique<Ball>(window.getRenderer(), Vector2{0.f, -0.33f}, 0.025f, Color{ 0, 0, 255, 255 });
	_paddle = std::make_unique<Paddle>(window.getRenderer(), Vector2{ 0.f, -0.9f }, 0.5f, 0.1f, Color{ 0, 255, 0, 255 });

	for (const auto& row : _blocks_grid)
		for (const auto& block : row)
		{
			_drawables.push_back(block.get());
		}

	_drawables.push_back(_ball.get());
	_drawables.push_back(_paddle.get());
}


void Application::processFrame(double time_since_start, float delta_time)
{
	window.getRenderer().clearBuffer(0.4f, 0.4f, 0.4f);

	for (auto& drawable : _drawables)
	{
		drawable->updatePositionUsingVelocity(delta_time);
		drawable->draw(window.getRenderer());
	}

	window.getRenderer().present();
}
