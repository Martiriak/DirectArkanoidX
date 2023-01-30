// Alessandro Pegoraro - Graphics Programming

#pragma once

#include <unordered_map>
#include <array>
#include "Drawables/Ball.h"
#include "Drawables/DestructibleBlock.h"
#include "Drawables/Paddle.h"
#include "Grid.h"


enum class GameProgress
{
	Normal,
	Lost,
	Won
};


class CollisionHandler
{
public:

	CollisionHandler(Grid::Type& blocks_grid, Ball& ball, Paddle& paddle);

	GameProgress checkForCollisions();

private:

	Grid::Type* _grid;
	Ball* _ball;
	Paddle* _paddle;
};
