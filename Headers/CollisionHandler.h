// Alessandro Pegoraro - Graphics Programming

#pragma once

#include <unordered_map>
#include <array>
#include "Drawables/Ball.h"
#include "Drawables/DestructibleBlock.h"
#include "Drawables/Paddle.h"
#include "Application.h"


class CollisionHandler
{
public:

	using BlocksGrid = std::array<std::array<std::unique_ptr<DestructibleBlock>, Application::grid_dim_Y>, Application::grid_dim_X>;

	CollisionHandler(BlocksGrid& blocks_grid, Ball& ball, Paddle& paddle);

	bool checkForCollisions();

private:

	std::unordered_map<Vector2, DestructibleBlock*> _collidable_blocks_in_grid;
	Ball* _ball;
	Paddle* _paddle;

	BlocksGrid* _grid;
	std::vector<std::pair<Vector2, DestructibleBlock*>> _new_candidates_for_collision;
};
