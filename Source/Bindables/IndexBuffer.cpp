// Alessandro Pegoraro - Graphics Programming

#include "Bindables/IndexBuffer.h"
#include "DirectXThrowMacros.h"


IndexBuffer::IndexBuffer(Renderer& renderer)
	: IndexBuffer(renderer, std::vector<uint16>()) { }

IndexBuffer::IndexBuffer(Renderer& renderer, const std::vector<uint16>& indices)
	: _indices(indices)
{
	makeBuffer(renderer);
}

IndexBuffer::IndexBuffer(Renderer& renderer, std::vector<uint16>&& indices)
	: _indices(std::move(indices))
{
	makeBuffer(renderer);
}


void IndexBuffer::makeBuffer(Renderer& renderer)
{
	HRESULT h_result;

	D3D11_BUFFER_DESC index_buffer_descriptor = { };
	index_buffer_descriptor.BindFlags            = D3D11_BIND_INDEX_BUFFER;
	index_buffer_descriptor.Usage                = D3D11_USAGE_DEFAULT;
	index_buffer_descriptor.CPUAccessFlags       = 0u;
	index_buffer_descriptor.MiscFlags            = 0u;
	index_buffer_descriptor.ByteWidth            = sizeof(uint16) * _indices.size();
	index_buffer_descriptor.StructureByteStride  = sizeof(uint16);

	D3D11_SUBRESOURCE_DATA index_buffer_subresource = { };
	index_buffer_subresource.pSysMem = _indices.data();

	THROW_IF_FAILED(getDevice(renderer)->CreateBuffer(&index_buffer_descriptor, &index_buffer_subresource, &_index_buffer));
}


void IndexBuffer::bindTo(Renderer& renderer) noexcept
{
	constexpr UINT index_offset = 0u;
	getContext(renderer)->IASetIndexBuffer(_index_buffer.Get(), DXGI_FORMAT_R16_UINT, index_offset);
}
