// Alessandro Pegoraro - Graphics Programming

#include "Bindables/VertexBuffer.h"
#include "DirectXThrowMacros.h"


VertexBuffer::VertexBuffer(Renderer& renderer)
	: VertexBuffer(renderer, std::vector<Vertex>()) { }

VertexBuffer::VertexBuffer(Renderer& renderer, const std::vector<Vertex>& vertices)
	: _vertices(vertices)
{
	makeBuffer(renderer);
}

VertexBuffer::VertexBuffer(Renderer& renderer, std::vector<Vertex>&& vertices)
	: _vertices(std::move(vertices))
{
	makeBuffer(renderer);
}


void VertexBuffer::makeBuffer(Renderer& renderer)
{
	HRESULT h_result;

	D3D11_BUFFER_DESC vertex_buffer_descriptor = { };
	vertex_buffer_descriptor.BindFlags            = D3D11_BIND_VERTEX_BUFFER;
	vertex_buffer_descriptor.Usage                = D3D11_USAGE_DEFAULT;
	vertex_buffer_descriptor.CPUAccessFlags       = 0u;
	vertex_buffer_descriptor.MiscFlags            = 0u;
	vertex_buffer_descriptor.ByteWidth            = sizeof(Vertex) * _vertices.size();
	vertex_buffer_descriptor.StructureByteStride  = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA vertex_buffer_subresource = { };
	vertex_buffer_subresource.pSysMem = _vertices.data();

	THROW_IF_FAILED(getDevice(renderer)->CreateBuffer(&vertex_buffer_descriptor, &vertex_buffer_subresource, &_vertex_buffer));
}


void VertexBuffer::bindTo(Renderer& renderer) noexcept
{
	constexpr UINT vertex_stride = sizeof(Vertex);
	constexpr UINT vertex_offset = 0u;
	getContext(renderer)->IASetVertexBuffers(0u, 1u, _vertex_buffer.GetAddressOf(), &vertex_stride, &vertex_offset);
}
