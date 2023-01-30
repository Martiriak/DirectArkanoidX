// Alessandro Pegoraro - Graphics Programming

#pragma once

#include <vector>
#include <array>
#include <memory>
#include "Window.h"
#include "Drawables/Ball.h"
#include "Drawables/DestructibleBlock.h"
#include "Drawables/Paddle.h"
#include "CollisionHandler.h"
#include "Grid.h"


class Application
{
public:

	Window window;

	Application() = delete;
	Application(int window_width, int window_height, LPCSTR window_name);

	void startGame(Vector2 ball_direction, float speed);
	void processFrame(double time_since_start, float delta_time);

private:

	Grid::Type _blocks_grid;
	std::unique_ptr<Ball> _ball;
	std::unique_ptr<Paddle> _paddle;
	std::unique_ptr<CollisionHandler> _collision_handler;

	bool _is_game_running = false;


	static constexpr Vector2 _ball_default_position = { 0.f, -0.8f };
	static constexpr float _ball_radius = 0.025f;

	static constexpr Vector2 _paddle_default_position = { 0.f, -0.9f };
	static constexpr Vector2 _paddle_dimensions = { 0.45f, 0.05f };

	static constexpr Vector2 _ball_velocity_direction = { -0.3f, 0.7f };
	static constexpr float _ball_speed = 1.5f;
	static constexpr float _paddle_speed = 1.f;


	void resetGame();
};
