// Alessandro Pegoraro - Graphics Programming

#include "Bindables/PixelShader.h"
#include <d3dcompiler.h>
#include "DirectXThrowMacros.h"

#pragma comment(lib,"D3DCompiler.lib")


PixelShader::PixelShader(Renderer& renderer, LPCWSTR compiled_shader_path)
{
	HRESULT h_result;

	THROW_IF_FAILED(D3DReadFileToBlob(compiled_shader_path, &_binary_data));
	THROW_IF_FAILED(getDevice(renderer)->CreatePixelShader
	(
		getBlob()->GetBufferPointer(),
		getBlob()->GetBufferSize(),
		nullptr,
		&_pixel_shader
	));
}


void PixelShader::bindTo(Renderer& renderer) noexcept
{
	getContext(renderer)->PSSetShader(_pixel_shader.Get(), nullptr, 0u);
}
