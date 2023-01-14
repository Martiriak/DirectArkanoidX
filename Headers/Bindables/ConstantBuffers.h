// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Bindables/Bindable.h"


template<typename Element>
class ConstantBuffer : public IBindable
{
public:

	ConstantBuffer(Renderer& renderer) { makeBuffer(renderer, nullptr, sizeof(Element)); }
	ConstantBuffer(Renderer& renderer, const Element& elements) { makeBuffer(renderer, &elements, sizeof(elements)); }


	void updateElements(Renderer& renderer, const Element& elements)
	{
		D3D11_MAPPED_SUBRESOURCE mapped_subresource = { };

		getContext(renderer)->Map
		(
			_constant_buffer.Get(),
			0u,
			D3D11_MAP_WRITE_DISCARD,
			0u,
			&mapped_subresource
		);

		memcpy(mapped_subresource.pData, &elements, sizeof(elements));

		getContext(renderer)->Unmap(_constant_buffer.Get(), 0u);
	}

protected:

	Microsoft::WRL::ComPtr<ID3D11Buffer> _constant_buffer;

private:

	void makeBuffer(Renderer& renderer, const Element* elements, const UINT buffer_size)
	{
		D3D11_BUFFER_DESC constant_buffer_descriptor = { };
		constant_buffer_descriptor.BindFlags            = D3D11_BIND_CONSTANT_BUFFER;
		constant_buffer_descriptor.Usage                = D3D11_USAGE_DYNAMIC;
		constant_buffer_descriptor.CPUAccessFlags       = D3D11_CPU_ACCESS_WRITE;
		constant_buffer_descriptor.MiscFlags            = 0u;
		constant_buffer_descriptor.ByteWidth            = buffer_size;
		constant_buffer_descriptor.StructureByteStride  = sizeof(Element);

		if (elements != nullptr)
		{
			D3D11_SUBRESOURCE_DATA constant_buffer_subresource = { };
			constant_buffer_subresource.pSysMem = elements;

			// No use of macro to not include and pollute namespace.

			HRESULT h_result =
				getDevice(renderer)->CreateBuffer(&constant_buffer_descriptor, &constant_buffer_subresource, &_constant_buffer);

			if (FAILED(h_result))
				throw Renderer::Exception(__LINE__, __FILE__, h_result);
		}
		else
		{
			HRESULT h_result =
				getDevice(renderer)->CreateBuffer(&constant_buffer_descriptor, nullptr, &_constant_buffer);

			if (FAILED(h_result))
				throw Renderer::Exception(__LINE__, __FILE__, h_result);
		}
	}
};


template<typename Element>
class VertexConstantBuffer : public ConstantBuffer<Element>
{
	using ConstantBuffer<Element>::_constant_buffer;
	using IBindable::getContext;

public:

	using ConstantBuffer<Element>::ConstantBuffer; // Reuse of base constructors.


	void bindTo(Renderer& renderer) noexcept override
	{
		getContext(renderer)->VSSetConstantBuffers(0u, 1u, _constant_buffer.GetAddressOf());
	}
};

template<typename Element>
class PixelConstantBuffer : public ConstantBuffer<Element>
{
	using ConstantBuffer<Element>::_constant_buffer;
	using IBindable::getContext;

public:

	using ConstantBuffer<Element>::ConstantBuffer; // Reuse of base constructors.


	void bindTo(Renderer& renderer) noexcept override
	{
		getContext(renderer)->PSSetConstantBuffers(0u, 1u, _constant_buffer.GetAddressOf());
	}
};
