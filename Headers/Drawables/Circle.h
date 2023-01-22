// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Drawables/DrawableStatics.h"


class Circle : public DrawableStatics<Circle>
{
public:

	Circle(Renderer& renderer, float center_x, float center_y, float radius, const struct Color& color);
	Circle(Renderer& renderer, float center_x, float center_y, float radius, const struct Color& color, const struct Color& center_color);

	void update(double total_time_passed, float delta_time) noexcept override;

private:

	static constexpr unsigned int vertices_number = 12;
};
