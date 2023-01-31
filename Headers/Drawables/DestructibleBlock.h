// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Drawables/Quad.h"


/**
 * Represents a single block which can be destroyed by the Ball.
 */
class DestructibleBlock : public Quad
{
public:

	using Quad::Quad;


	virtual void handleCollision(Vector2 surface_normal) noexcept override;

private:

	
};
