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


/**
 * Does collision detection for the Ball and all other Quads in the scene. It usually gets initialized by an Application.
 * 
 * @see Drawables/Ball, Drawables/Quad, Application
 */
class CollisionHandler
{
public:

	CollisionHandler(Grid::Type& blocks_grid, Ball& ball, Paddle& paddle);

	/**
	 * Checks for collision between the Ball and any other Quad (Paddle and DestructibleBlocks).
	 * 
	 * @returns If all the DestructibleBlocks have been destroyed, returns GameProgress::Won. If the Ball touches the lower border of the screen, returns GameProgress::Lost. Otherwise, returns GameProgress::Normal.
	 */
	GameProgress checkForCollisions();

private:

	Grid::Type* _grid;
	Ball* _ball;
	Paddle* _paddle;
};
