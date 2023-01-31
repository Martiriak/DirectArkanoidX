// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Drawables/Quad.h"


/**
 * Represents the paddle that the player can move at the bottom of the screen.
 */
class Paddle : public Quad
{
public:

	using Quad::Quad;


	virtual void handleCollision(Vector2 surface_normal) noexcept override;

private:


};
