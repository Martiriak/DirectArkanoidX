// Alessandro Pegoraro - Graphics Programming

#include "Bindables/Bindable.h"
#include "Renderer.h"


ID3D11Device* IBindable::getDevice(Renderer& renderer) noexcept
{
	return renderer._device.Get();
}

ID3D11DeviceContext* IBindable::getContext(Renderer& renderer) noexcept
{
	return renderer._device_context.Get();
}
