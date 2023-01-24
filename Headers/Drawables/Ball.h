// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Drawables/DrawableStatics.h"


class Ball : public DrawableStatics<Ball>
{
public:

	Ball(Renderer& renderer, float center_x, float center_y, float radius, const struct Color& color);
	Ball(Renderer& renderer, float center_x, float center_y, float radius, const struct Color& color, const struct Color& center_color);

	virtual void handleCollision() noexcept override;

private:

	static constexpr unsigned int vertices_number = 12;
};
