// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Bindables/Bindable.h"


class VertexShader : public IBindable
{
public:

	VertexShader(Renderer& renderer, LPCWSTR compiled_shader_path);

	void bindTo(Renderer& renderer) noexcept override;

	inline LPVOID getBlobBufferPointer() const { return _binary_data->GetBufferPointer(); }
	inline SIZE_T getBlobBufferSize() const { return _binary_data->GetBufferSize(); }

private:

	Microsoft::WRL::ComPtr<ID3DBlob> _binary_data;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> _vertex_shader;
};
