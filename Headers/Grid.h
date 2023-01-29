// Alessandro Pegoraro - Graphics Programming

#pragma once

#include <memory>
#include <array>
#include "Drawables/DestructibleBlock.h"


namespace Grid
{
	constexpr int dim_X = 10;
	constexpr int dim_Y = 8;

	using Type = std::array<std::array<std::unique_ptr<DestructibleBlock>, dim_Y>, dim_X>;
}
