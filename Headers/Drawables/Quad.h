// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Drawables/DrawableStatics.h"
#include "Vertex.h"


class Quad : public DrawableStatics<Quad>
{
public:

	Quad(Renderer& renderer, float center_point_x, float center_point_y, float width, float height, const Color& color);

private:
	

};
