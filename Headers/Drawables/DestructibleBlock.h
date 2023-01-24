// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Drawables/Quad.h"


class DestructibleBlock : public Quad
{
public:

	using Quad::Quad;


	virtual void handleCollision() noexcept override;

private:

	
};
