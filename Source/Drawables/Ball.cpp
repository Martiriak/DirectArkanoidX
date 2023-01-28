// Alessandro Pegoraro - Graphics Programming

#include "Drawables/Ball.h"
#include "Vertex.h"
#include "Bindables/VertexBuffer.h"
#include "Bindables/IndexBuffer.h"
#include "Bindables/InputLayout.h"
#include "Bindables/Topology.h"
#include "Bindables/VertexShader.h"
#include "Bindables/PixelShader.h"
#include "Bindables/ConstantBuffers.h"


Ball::Ball(Renderer& renderer, Vector2 center, float radius, const Color& color)
	: Ball(renderer, center, radius, color, color) { }

Ball::Ball(Renderer& renderer, Vector2 center, float radius, const struct Color& color, const struct Color& center_color)
{
	static_assert(vertices_number > 2, "vertices_number must be greater than 2.");

	position = center;

	// Make Vertices //

	std::vector<Vertex> vertices; vertices.reserve(vertices_number + 1);

	{
		constexpr float angle_between_points = DirectX::XM_2PI / vertices_number;

		for (int vertex_index = 0; vertex_index < vertices_number; ++vertex_index)
		{
			const float x = radius * DirectX::XMScalarSin(angle_between_points * vertex_index);
			const float y = radius * DirectX::XMScalarCos(angle_between_points * vertex_index);

			vertices.push_back({ {x, y}, {color} });
		}
	}

	vertices.push_back({ {0.f, 0.f}, {center_color} });

	addBind(std::make_unique<VertexBuffer>(renderer, vertices));

	// Make Indices //

	// The number of triangles that compose the circle is equal to vertices_number.
	std::vector<unsigned short> indices; indices.reserve(vertices_number * 3);

	{
		int triangle_index;
		for (triangle_index = 0; triangle_index < vertices_number - 1; ++triangle_index)
		{
			indices.push_back(triangle_index);
			indices.push_back(triangle_index + 1);
			indices.push_back(vertices_number);
		}

		indices.push_back(triangle_index);
		indices.push_back(0);
		indices.push_back(vertices_number);
	}

	setIndexBuffer(std::make_unique<IndexBuffer>(renderer, indices));


	if (!areStaticsInitialized())
	{
		std::unique_ptr<VertexShader> vertex_shader = std::make_unique<VertexShader>(renderer, L"Shaders\\VertexShader.cso");
		auto vertex_shader_bytecode = vertex_shader->getBlob();

		addStaticBind(std::move(vertex_shader));
		addStaticBind(std::make_unique<PixelShader>(renderer, L"Shaders\\PixelShader.cso"));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> input_element_descriptors =
		{
			{ "Position", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u },
			{ "Color", 0u, DXGI_FORMAT_R8G8B8A8_UNORM, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u }
		};

		addStaticBind(std::make_unique<InputLayout>(renderer, input_element_descriptors, vertex_shader_bytecode));
		addStaticBind(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
}


void Ball::handleCollision() noexcept
{

}
