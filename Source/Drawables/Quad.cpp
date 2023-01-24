// Alessandro Pegoraro - Graphics Programming

#include "Drawables/Quad.h"
#include "Bindables/VertexBuffer.h"
#include "Bindables/IndexBuffer.h"
#include "Bindables/InputLayout.h"
#include "Bindables/Topology.h"
#include "Bindables/VertexShader.h"
#include "Bindables/PixelShader.h"
#include "Bindables/ConstantBuffers.h"


Quad::Quad(Renderer& renderer, float center_point_x, float center_point_y, float width, float height, const Color& color)
{
	position = { center_point_x, center_point_y };

	const Vertex upper_left = { {-width / 2.f, height / 2.f}, {color} };
	const Vertex downer_right = { {width / 2.f, -height / 2.f}, {color} };
	const Vertex upper_right = { {downer_right.position.x, upper_left.position.y}, {color} };
	const Vertex downer_left = { {upper_left.position.x, downer_right.position.y}, {color} };

	const std::vector<Vertex> vertices = { upper_left, upper_right, downer_left, downer_right };

	addBind(std::make_unique<VertexBuffer>(renderer, vertices));

	if (!areStaticsInitialized())
	{
		std::unique_ptr<VertexShader> vertex_shader = std::make_unique<VertexShader>(renderer, L"Shaders\\VertexShader.cso");
		auto vertex_shader_bytecode = vertex_shader->getBlob();

		addStaticBind(std::move(vertex_shader));
		addStaticBind(std::make_unique<PixelShader>(renderer, L"Shaders\\PixelShader.cso"));

		const std::vector<unsigned short> indices =
		{
			0, 1, 2,
			2, 1, 3
		};

		setStaticIndexBuffer(std::make_unique<IndexBuffer>(renderer, indices));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> input_element_descriptors =
		{
			{ "Position", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u },
			{ "Color", 0u, DXGI_FORMAT_R8G8B8A8_UNORM, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u }
		};

		addStaticBind(std::make_unique<InputLayout>(renderer, input_element_descriptors, vertex_shader_bytecode));
		addStaticBind(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		setIndexFromStatic();
	}
}
