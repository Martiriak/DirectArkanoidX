// Alessandro Pegoraro - Graphics Programming

#pragma once

#include <memory>
#include <array>
#include "Drawables/DestructibleBlock.h"


namespace Grid
{
	constexpr int dim_X = 10;
	constexpr int dim_Y = 8;

	constexpr float blocks_height = 0.075f;
	constexpr float blocks_width = 0.25f;
	constexpr Vector2 base_point = { -1.f + blocks_width * 0.5f, 1.f - blocks_height * 0.5f };
	constexpr float offset_x = (2.f - blocks_width) / (dim_Y - 1);
	constexpr float offset_y = blocks_height;

	using Type = std::array<std::array<std::unique_ptr<DestructibleBlock>, dim_Y>, dim_X>;
}
