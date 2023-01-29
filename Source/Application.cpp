// Alessandro Pegoraro - Graphics Programming

#include "Application.h"
#include <string>
#include "Color.h"


Application::Application(int window_width, int window_height, LPCSTR window_name)
	: window(window_width, window_height, window_name)
{
	const float blocks_height = 0.075f;
	const float blocks_width = 0.25f;
	const Vector2 base_point = { -1.f + blocks_width * 0.5f, 1.f - blocks_height * 0.5f };
	const float offset_x = (2.f - blocks_width) / (Grid::dim_Y - 1);
	const float offset_y = blocks_height;

	for (int x = 0; x < _blocks_grid.size(); ++x)
		for (int y = 0; y < _blocks_grid[x].size(); ++y)
		{
			_blocks_grid[x][y] = std::make_unique<DestructibleBlock>
			(
				window.getRenderer(),
				base_point + Vector2{ offset_x * y, -offset_y * x },
				blocks_width,
				blocks_height,
				Color::white(),
				Color::gray()
			);
		}

	_ball = std::make_unique<Ball>(window.getRenderer(), Vector2{0.f, -0.33f}, 0.025f, Color::orange());
	_paddle = std::make_unique<Paddle>(window.getRenderer(), Vector2{ 0.f, -0.9f }, 0.5f, 0.1f, Color::cyan(), Color::magenta());

	_collision_handler = std::make_unique<CollisionHandler>(_blocks_grid, *_ball, *_paddle);

	_ball->velocity = Vector2{ -0.5f, 0.5f }.getNormalized() * 2.f;
}


void Application::processFrame(double time_since_start, float delta_time)
{
	window.getRenderer().clearBuffer(0.4f, 0.4f, 0.4f);

	if (_collision_handler->checkForCollisions())
	{
		// You won!
	}

	for (const auto& row : _blocks_grid)
		for (const auto& block : row)
		{
			if (block)
			{
				//block->updatePositionUsingVelocity(delta_time);
				block->draw(window.getRenderer());
			}
		}

	_ball->updatePositionUsingVelocity(delta_time);
	_ball->draw(window.getRenderer());
	_paddle->updatePositionUsingVelocity(delta_time);
	_paddle->draw(window.getRenderer());

	window.getRenderer().present();
}
