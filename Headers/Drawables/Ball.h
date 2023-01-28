// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Drawables/DrawableStatics.h"
#include "Vector2.h"
#include "Color.h"


class Ball : public DrawableStatics<Ball>
{
public:

	Ball(Renderer& renderer, Vector2 center, float radius, const struct Color& color);
	Ball(Renderer& renderer, Vector2 center, float radius, const struct Color& color, const struct Color& center_color);

	virtual void handleCollision() noexcept override;

private:

	static constexpr unsigned int vertices_number = 12;
};
