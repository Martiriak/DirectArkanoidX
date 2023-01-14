// Alessandro Pegoraro - Graphics Programming

#include "Bindables/Topology.h"


Topology::Topology(D3D11_PRIMITIVE_TOPOLOGY primitive_topology)
	: _primitive_topology(primitive_topology) { }


void Topology::bindTo(Renderer& renderer) noexcept
{
	getContext(renderer)->IASetPrimitiveTopology(_primitive_topology);
}
