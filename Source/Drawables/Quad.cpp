// Alessandro Pegoraro - Graphics Programming

#include "Drawables/Quad.h"
#include "Bindables/VertexBuffer.h"
#include "Bindables/IndexBuffer.h"
#include "Bindables/InputLayout.h"
#include "Bindables/Topology.h"
#include "Bindables/VertexShader.h"
#include "Bindables/PixelShader.h"
#include "Bindables/ConstantBuffers.h"


Quad::Quad(Renderer& renderer, const Vertex& upper_left, const Vertex& upper_right, const Vertex& downer_left, const Vertex& downer_right)
{
	const std::vector<Vertex> vertices = { upper_left, upper_right, downer_left, downer_right };


	addBind(std::make_unique<VertexBuffer>(renderer, vertices));
}


void Quad::update(double total_time_passed, float delta_time) noexcept
{
	_rotation_angle = delta_time;
}
