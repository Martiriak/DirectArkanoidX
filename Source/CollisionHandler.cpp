// Alessandro Pegoraro - Graphics Programming

#include "CollisionHandler.h"


namespace
{
	bool areIntersecting(const Ball& ball, const Quad& quad)
	{
		const float squared_radius = ball.getRadius() * ball.getRadius();
		const Vector2 ball_to_quad = quad.position - ball.position;

		if (squared_radius >= ball_to_quad.getSquaredLenght()) return true;

		const Vector2 plus_width_plus_height    = { ball_to_quad.x + quad.getWidth(), ball_to_quad.y + quad.getHeight() };
		const Vector2 plus_width_minus_height   = { ball_to_quad.x + quad.getWidth(), ball_to_quad.y - quad.getHeight() };
		const Vector2 minus_width_plus_height   = { ball_to_quad.x - quad.getWidth(), ball_to_quad.y + quad.getHeight() };
		const Vector2 minus_width_minus_height  = { ball_to_quad.x - quad.getWidth(), ball_to_quad.y - quad.getHeight() };

		return squared_radius == plus_width_plus_height.getSquaredLenght()
			|| squared_radius == plus_width_minus_height.getSquaredLenght()
			|| squared_radius == minus_width_plus_height.getSquaredLenght()
			|| squared_radius == minus_width_minus_height.getSquaredLenght();
	}

	inline bool isOutOfBounds(const Vector2& grid_pos)
	{
		return grid_pos.x < 0 || grid_pos.x > Application::grid_dim_X - 1
			|| grid_pos.y < 0 || grid_pos.y > Application::grid_dim_Y - 1;
	}
}

using grid_cell = std::pair<Vector2, DestructibleBlock*>;


CollisionHandler::CollisionHandler(BlocksGrid& blocks_grid, Ball& ball, Paddle& paddle)
	: _grid(&blocks_grid), _ball(&ball), _paddle(&paddle)
{
	const int last_row_index = blocks_grid.size() - 1;

	// Insert each block in the last row into _collidable_blocks_in_grid.
	for (int y = 0; y < blocks_grid[last_row_index].size(); ++y)
	{
		_collidable_blocks_in_grid.insert(grid_cell(Vector2(last_row_index , y), blocks_grid[last_row_index][y].get()));
	}

	_new_candidates_for_collision.reserve(8);
}

bool CollisionHandler::checkForCollisions()
{
	if (areIntersecting(*_ball, *_paddle))
	{
		_ball->handleCollision(Vector2::up());
		_paddle->handleCollision(_ball->velocity.getNormalized());
	}
	else 
	{
		auto it = _collidable_blocks_in_grid.begin();

		while (it != _collidable_blocks_in_grid.end())
		{
			if (it->second != nullptr && areIntersecting(*_ball, *it->second))
			{
				_ball->handleCollision(-Vector2::up());
				it->second->handleCollision(_ball->velocity.getNormalized());

				const Vector2 left_block = it->first - Vector2::right();
				const Vector2 right_block = it->first + Vector2::right();
				const Vector2 up_block = it->first - Vector2::up();

				_new_candidates_for_collision.push_back(grid_cell(left_block, (*_grid)[left_block.x][left_block.y].get()));
				_new_candidates_for_collision.push_back(grid_cell(right_block, (*_grid)[right_block.x][right_block.y].get()));
				_new_candidates_for_collision.push_back(grid_cell(up_block, (*_grid)[up_block.x][up_block.y].get()));

				it = _collidable_blocks_in_grid.erase(it);
			}
		}

		if (_ball->position.x > 1.f) _ball->handleCollision(-Vector2::right());
		if (_ball->position.x < -1.f) _ball->handleCollision(Vector2::right());
		if (_ball->position.y > 1.f) _ball->handleCollision(-Vector2::up());
		if (_ball->position.y < -1.f) _ball->handleCollision(Vector2::up()); // This is game over!
	}

	for (auto& candidate : _new_candidates_for_collision)
	{
		if (!isOutOfBounds(candidate.first) && candidate.second != nullptr)
		{
			_collidable_blocks_in_grid.insert(candidate);
		}
	}

	return _collidable_blocks_in_grid.size() > 0;
}
