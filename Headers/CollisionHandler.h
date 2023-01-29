// Alessandro Pegoraro - Graphics Programming

#pragma once

#include <unordered_map>
#include <array>
#include "Drawables/Ball.h"
#include "Drawables/DestructibleBlock.h"
#include "Drawables/Paddle.h"
#include "Grid.h"


class CollisionHandler
{
public:

	CollisionHandler(Grid::Type& blocks_grid, Ball& ball, Paddle& paddle);

	bool checkForCollisions();

private:

	std::unordered_map<Vector2, DestructibleBlock*> _collidable_blocks_in_grid;
	Ball* _ball;
	Paddle* _paddle;

	Grid::Type* _grid;
	std::vector<std::pair<Vector2, DestructibleBlock*>> _new_candidates_for_collision;
};
