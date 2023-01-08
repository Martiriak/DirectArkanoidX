// Alessandro Pegoraro - Graphics Programming

#pragma once


class IBindable
{
public:

	virtual void bindTo(class Renderer& renderer) noexcept = 0;
	virtual ~IBindable() noexcept = default;

protected:

	static struct ID3D11Device* getDevice(class Renderer& renderer) noexcept;
	static struct ID3D11DeviceContext* getContext(class Renderer& renderer) noexcept;
};
