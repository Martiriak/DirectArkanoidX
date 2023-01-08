// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Bindables/Bindable.h"
#include <vector>
#include "Vertex.h"


class VertexBuffer : public IBindable
{
public:

	VertexBuffer(Renderer& renderer);
	VertexBuffer(Renderer& renderer, const std::vector<Vertex>& vertices);
	VertexBuffer(Renderer& renderer, std::vector<Vertex>&& vertices);

	void bindTo(Renderer& renderer) noexcept override;

private:

	std::vector<Vertex> _vertices;
	Microsoft::WRL::ComPtr<ID3D11Buffer> _vertex_buffer;

	void makeBuffer(Renderer& renderer);
};
