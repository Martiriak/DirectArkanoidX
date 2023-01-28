// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Drawables/DrawableStatics.h"
#include "Vector2.h"
#include "Color.h"


class Quad : public DrawableStatics<Quad>
{
public:

	Quad(Renderer& renderer, Vector2 center_point, float width, float height, const Color& color);

private:
	

};
