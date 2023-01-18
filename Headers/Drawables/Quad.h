// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Drawables/DrawableStatics.h"
#include "Vertex.h"


class Quad : public DrawableStatics<Quad>
{
public:

	Quad(Renderer& renderer, const Vertex& upper_left, const Vertex& upper_right, const Vertex& downer_left, const Vertex& downer_right);

	DirectX::XMMATRIX getTransformMatrix() const noexcept override;
	void update(double total_time_passed, float delta_time) noexcept override;

private:

	float _rotation_angle = 0.f;
};
