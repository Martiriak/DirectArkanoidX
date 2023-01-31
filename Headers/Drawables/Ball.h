// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Drawables/DrawableStatics.h"
#include "Vector2.h"
#include "Color.h"


/**
 * Represents the sphere which gets bounced around and that destroys the blocks in the grid.
 */
class Ball : public DrawableStatics<Ball>
{
public:

	inline Ball(Renderer& renderer, Vector2 center, float radius, const struct Color& color)
		: Ball(renderer, center, radius, color, color) { }
	Ball(Renderer& renderer, Vector2 center, float radius, const struct Color& color, const struct Color& center_color);

	virtual void handleCollision(Vector2 surface_normal) noexcept override;

	inline float getRadius() const noexcept { return _radius; }

private:

	float _radius;

	static constexpr unsigned int vertices_number = 12;
};
