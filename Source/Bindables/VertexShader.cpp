// Alessandro Pegoraro - Graphics Programming

#include "Bindables/VertexShader.h"
#include <d3dcompiler.h>
#include "DirectXThrowMacros.h"

#pragma comment(lib,"D3DCompiler.lib")


VertexShader::VertexShader(Renderer& renderer, LPCWSTR compiled_shader_path)
{
	HRESULT h_result;

	THROW_IF_FAILED(D3DReadFileToBlob(compiled_shader_path, &_binary_data));
	THROW_IF_FAILED(getDevice(renderer)->CreateVertexShader(getBlobBufferPointer(), getBlobBufferSize(), nullptr, &_vertex_shader));
}


void VertexShader::bindTo(Renderer& renderer) noexcept
{
	getContext(renderer)->VSSetShader(_vertex_shader.Get(), nullptr, 0u);
}
