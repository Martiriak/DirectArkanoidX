// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Renderer.h"


/**
 * Interface for all objects representing a DirectX resource.
 */
class IBindable
{
public:

	/**
	 * Sets this resource as the one currently used by the Renderer.
	 */
	virtual void bindTo(Renderer& renderer) noexcept = 0;
	virtual ~IBindable() noexcept = default;

protected:

	// These methods provide to children classes access to DirectX device and device context.
	// These normally aren't accessible by external classes, but IBindable is a friend of Renderer
	// (although its children are not, hence the need for these methods).

	static ID3D11Device* getDevice(Renderer& renderer) noexcept;
	static ID3D11DeviceContext* getContext(Renderer& renderer) noexcept;
};
