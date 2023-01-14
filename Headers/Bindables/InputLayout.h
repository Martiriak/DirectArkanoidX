// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Bindables/Bindable.h"
#include <vector>


class InputLayout : public IBindable
{
public:

	InputLayout(Renderer& renderer, const std::vector<D3D11_INPUT_ELEMENT_DESC>& descriptors, ID3DBlob* vertex_shader_code);
	
	void bindTo(Renderer& renderer) noexcept override;

private:

	Microsoft::WRL::ComPtr<ID3D11InputLayout> _input_layout;
};