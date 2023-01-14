// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Bindables/Bindable.h"


class PixelShader : public IBindable
{
public:

	PixelShader(Renderer& renderer, LPCWSTR compiled_shader_path);

	void bindTo(Renderer& renderer) noexcept override;

	inline ID3DBlob* getBlob() const { return _binary_data.Get(); }

private:

	Microsoft::WRL::ComPtr<ID3DBlob> _binary_data;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> _pixel_shader;
};
