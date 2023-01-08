// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Renderer.h"


class IBindable
{
public:

	virtual void bindTo(Renderer& renderer) noexcept = 0;
	virtual ~IBindable() noexcept = default;

protected:

	static ID3D11Device* getDevice(Renderer& renderer) noexcept;
	static ID3D11DeviceContext* getContext(Renderer& renderer) noexcept;
};
