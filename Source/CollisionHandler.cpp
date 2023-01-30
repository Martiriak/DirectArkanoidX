// Alessandro Pegoraro - Graphics Programming

#include "CollisionHandler.h"
#include <cmath>


namespace
{
	bool areIntersecting(const Ball& ball, const Quad& quad)
	{
		const float squared_radius = ball.getRadius() * ball.getRadius();
		const Vector2 quad_to_ball = { std::abs(ball.position.x - quad.position.x), std::abs(ball.position.y - quad.position.y) };

		if (quad_to_ball.x > (quad.getWidth() * 0.5f + ball.getRadius())) return false;
		if (quad_to_ball.y > (quad.getHeight() * 0.5f + ball.getRadius())) return false;

		if (quad_to_ball.x <= (quad.getWidth() * 0.5f)) return true;
		if (quad_to_ball.y <= (quad.getHeight() * 0.5f)) return true;

		const float corner_distance_squared =
			Vector2{ quad_to_ball.x - quad.getWidth() * 0.5f, quad_to_ball.y - quad.getHeight() * 0.5f }.getSquaredLenght();

		return corner_distance_squared <= squared_radius;
	}

	inline bool isOutOfBounds(const Vector2& grid_pos)
	{
		return grid_pos.x < 0 || grid_pos.x > Grid::dim_X - 1
			|| grid_pos.y < 0 || grid_pos.y > Grid::dim_Y - 1;
	}
}




CollisionHandler::CollisionHandler(Grid::Type& blocks_grid, Ball& ball, Paddle& paddle)
	: _grid(&blocks_grid), _ball(&ball), _paddle(&paddle)
{ }


GameProgress CollisionHandler::checkForCollisions()
{
	bool no_remaining_block = true;

	if (areIntersecting(*_ball, *_paddle))
	{
		_ball->handleCollision(Vector2::up());
		_paddle->handleCollision(_ball->velocity.getNormalized());

		// Safety measure.
		no_remaining_block = false;
	}
	else 
	{
		for (auto& row : *_grid)
			for (auto& block : row)
			{
				if (block)
				{
					no_remaining_block = false;

					if (areIntersecting(*_ball, *block))
					{
						_ball->handleCollision(-Vector2::up());
						block->handleCollision(_ball->velocity.getNormalized());

						block.release();
					}
				}
			}

		if (_ball->position.x > 1.f) _ball->handleCollision(-Vector2::right());
		if (_ball->position.x < -1.f) _ball->handleCollision(Vector2::right());
		if (_ball->position.y > 1.f) _ball->handleCollision(-Vector2::up());
		if (_ball->position.y < -1.f) return GameProgress::Lost;
	}

	if (_paddle->position.x - (_paddle->getWidth() * 0.5f) < -1.f)
	{
		_paddle->position = _paddle->position + Vector2{ 0.01f, 0.f };
		_paddle->velocity = Vector2::zero();
	}
	if (_paddle->position.x + (_paddle->getWidth() * 0.5f) > 1.f)
	{
		_paddle->position = _paddle->position - Vector2{ 0.01f, 0.f };
		_paddle->velocity = Vector2::zero();
	}

	return no_remaining_block ? GameProgress::Won : GameProgress::Normal;
}
