// Alessandro Pegoraro - Graphics Programming

#include "Application.h"
#include <string>
#include "Color.h"


Application::Application(int window_width, int window_height, LPCSTR window_name)
	: window(window_width, window_height, window_name)
{
	// Grid, Ball and Paddle initialization.

	Color upper_corner_color;
	Color downer_corner_color;

	for (int x = 0; x < _blocks_grid.size(); ++x)
		for (int y = 0; y < _blocks_grid[x].size(); ++y)
		{
			switch (x % 4)
			{
			case 0:
				upper_corner_color = Color::red();
				downer_corner_color = Color::darkRed();
				break;
			case 1:
				upper_corner_color = Color::blue();
				downer_corner_color = Color::darkBlue();
				break;
			case 2:
				upper_corner_color = Color::green();
				downer_corner_color = Color::darkGreen();
				break;
			case 3:
				upper_corner_color = Color::white();
				downer_corner_color = Color::gray();
				break;
			}

			_blocks_grid[x][y] = std::make_unique<DestructibleBlock>
			(
				window.getRenderer(),
				Grid::base_point + Vector2{ Grid::offset_x * y, -Grid::offset_y * x },
				Grid::blocks_width,
				Grid::blocks_height,
				upper_corner_color,
				downer_corner_color
			);
		}

	_ball = std::make_unique<Ball>(window.getRenderer(), _ball_default_position, _ball_radius, Color::orange());
	_paddle = std::make_unique<Paddle>(window.getRenderer(), _paddle_default_position, _paddle_dimensions.x, _paddle_dimensions.y, Color::cyan(), Color::magenta());

	_collision_handler = std::make_unique<CollisionHandler>(_blocks_grid, *_ball, *_paddle);

	// For safety.
	_ball->velocity = Vector2::zero();
	_paddle->velocity = Vector2::zero();
}


void Application::startGame(Vector2 ball_direction, float speed)
{
	_ball->velocity = ball_direction.getNormalized() * speed;
	_is_game_running = true;
}

void Application::processFrame(double time_since_start, float delta_time)
{
	window.getRenderer().clearBuffer(0.4f, 0.4f, 0.4f);

	if (_is_game_running)
	{
		// Paddle movement.

		if (window.keyboard.isKeyPressed('A'))
			_paddle->velocity = -Vector2::right() * _paddle_speed;
		else if (window.keyboard.isKeyPressed('D'))
			_paddle->velocity = Vector2::right() * _paddle_speed;
		else
			_paddle->velocity = Vector2::zero();


		GameProgress progress = _collision_handler->checkForCollisions();

		if (progress == GameProgress::Lost)
		{
			MessageBox(nullptr, "You lost!", "Unfortunate.", MB_OK | MB_ICONEXCLAMATION);
			resetGame();
			return;
		}

		if (progress == GameProgress::Won)
		{
			MessageBox(nullptr, "You won!", "Congratulations!", MB_OK | MB_ICONINFORMATION);
			resetGame();
			return;
		}
	}
	else
	{
		if (window.keyboard.isKeyPressed(' ')) startGame(_ball_velocity_direction, _ball_speed);
	}


	// DRAW //

	for (const auto& row : _blocks_grid)
		for (const auto& block : row)
		{
			if (block)
			{
				block->draw(window.getRenderer());
			}
		}

	_ball->updatePositionUsingVelocity(delta_time);
	_ball->draw(window.getRenderer());
	_paddle->updatePositionUsingVelocity(delta_time);
	_paddle->draw(window.getRenderer());

	window.getRenderer().present();
}


void Application::resetGame()
{
	// Rebuilds blocks if they have been destroyed.

	Color upper_corner_color;
	Color downer_corner_color;

	for (int x = 0; x < _blocks_grid.size(); ++x)
		for (int y = 0; y < _blocks_grid[x].size(); ++y)
		{
			if (_blocks_grid[x][y] == nullptr)
			{
				switch (x % 4)
				{
				case 0:
					upper_corner_color = Color::red();
					downer_corner_color = Color::darkRed();
					break;
				case 1:
					upper_corner_color = Color::blue();
					downer_corner_color = Color::darkBlue();
					break;
				case 2:
					upper_corner_color = Color::green();
					downer_corner_color = Color::darkGreen();
					break;
				case 3:
					upper_corner_color = Color::white();
					downer_corner_color = Color::gray();
					break;
				}

				_blocks_grid[x][y] = std::make_unique<DestructibleBlock>
				(
					window.getRenderer(),
					Grid::base_point + Vector2{ Grid::offset_x * y, -Grid::offset_y * x },
					Grid::blocks_width,
					Grid::blocks_height,
					upper_corner_color,
					downer_corner_color
				);
			}
		}

	_ball->position = _ball_default_position;
	_ball->velocity = Vector2::zero();

	_paddle->position = _paddle_default_position;
	_paddle->velocity = Vector2::zero();

	_is_game_running = false;
}
