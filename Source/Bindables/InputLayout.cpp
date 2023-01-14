// Alessandro Pegoraro - Graphics Programming

#include "Bindables/InputLayout.h"
#include "DirectXThrowMacros.h"


InputLayout::InputLayout(Renderer& renderer, const std::vector<D3D11_INPUT_ELEMENT_DESC>& descriptors, ID3DBlob* vertex_shader_code)
{
	HRESULT h_result;

	THROW_IF_FAILED(getDevice(renderer)->CreateInputLayout
	(
		descriptors.data(),
		(UINT) descriptors.size(),
		vertex_shader_code->GetBufferPointer(),
		vertex_shader_code->GetBufferSize(),
		&_input_layout
	));
}


void InputLayout::bindTo(Renderer& renderer) noexcept
{
	getContext(renderer)->IASetInputLayout(_input_layout.Get());
}
