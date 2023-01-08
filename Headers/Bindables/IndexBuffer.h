// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Bindables/Bindable.h"
#include <vector>


class IndexBuffer : public IBindable
{
	using uint16 = unsigned short;

public:

	IndexBuffer(Renderer& renderer);
	IndexBuffer(Renderer& renderer, const std::vector<uint16>& indices);
	IndexBuffer(Renderer& renderer, std::vector<uint16>&& indices);

	inline UINT getIndicesNumber() const { return _indices.size(); }

	void bindTo(Renderer& renderer) noexcept override;

private:

	std::vector<uint16> _indices;
	Microsoft::WRL::ComPtr<ID3D11Buffer> _index_buffer;

	void makeBuffer(Renderer& renderer);
};
