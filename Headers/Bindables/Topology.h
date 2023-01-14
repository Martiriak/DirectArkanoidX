// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Bindables/Bindable.h"


class Topology : public IBindable
{
public:

	Topology(D3D11_PRIMITIVE_TOPOLOGY primitive_topology);

	void bindTo(Renderer& renderer) noexcept override;

private:

	D3D11_PRIMITIVE_TOPOLOGY _primitive_topology;
};
