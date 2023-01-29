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

using grid_cell = std::pair<Vector2, DestructibleBlock*>;


CollisionHandler::CollisionHandler(Grid::Type& blocks_grid, Ball& ball, Paddle& paddle)
	: _grid(&blocks_grid), _ball(&ball), _paddle(&paddle)
{
	const int last_row_index = blocks_grid.size() - 1;

	// Insert each block in the last row into _collidable_blocks_in_grid.
	for (int y = 0; y < blocks_grid[last_row_index].size(); ++y)
	{
		_collidable_blocks_in_grid.insert(grid_cell(Vector2(last_row_index, y), blocks_grid[last_row_index][y].get()));
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
			if (it->second == nullptr)
			{
				it = _collidable_blocks_in_grid.erase(it);
			}
			else if (areIntersecting(*_ball, *it->second))
			{
				_ball->handleCollision(-Vector2::up());
				it->second->handleCollision(_ball->velocity.getNormalized());

				const Vector2 left_block = it->first - Vector2::up();
				const Vector2 right_block = it->first + Vector2::up();
				const Vector2 up_block = it->first - Vector2::right();

				if (!isOutOfBounds(left_block))
					_new_candidates_for_collision.push_back(grid_cell(left_block, (*_grid)[left_block.x][left_block.y].get()));

				if (!isOutOfBounds(right_block))
					_new_candidates_for_collision.push_back(grid_cell(right_block, (*_grid)[right_block.x][right_block.y].get()));

				if (!isOutOfBounds(up_block))
					_new_candidates_for_collision.push_back(grid_cell(up_block, (*_grid)[up_block.x][up_block.y].get()));

				(*_grid)[it->first.x][it->first.y].release();
				it->second = nullptr;
				it = _collidable_blocks_in_grid.erase(it);
			}
			else ++it;
		}

		if (_ball->position.x > 1.f) _ball->handleCollision(-Vector2::right());
		if (_ball->position.x < -1.f) _ball->handleCollision(Vector2::right());
		if (_ball->position.y > 1.f) _ball->handleCollision(-Vector2::up());
		if (_ball->position.y < -1.f) _ball->handleCollision(Vector2::up()); // This is game over!
	}

	for (auto& candidate : _new_candidates_for_collision)
	{
		if (candidate.second != nullptr)
		{
			_collidable_blocks_in_grid.insert(candidate);
		}
	}

	return _collidable_blocks_in_grid.size() > 0;
}
