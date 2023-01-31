// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Drawables/DrawableStatics.h"
#include "Vector2.h"
#include "Color.h"


/**
 * Base class for axis aligned rectangular objects.
 */
class Quad : public DrawableStatics<Quad>
{
public:

	inline Quad(Renderer& renderer, Vector2 center_point, float width, float height, const Color& color)
		: Quad(renderer, center_point, width, height, color, color) { }

	Quad(Renderer& renderer, Vector2 center_point, float width, float height, const Color& top_left_color, const Color& down_right_color);


	inline float getWidth() const noexcept { return _width; }
	inline float getHeight() const noexcept { return _height; }

private:
	
	float _width;
	float _height;
};
