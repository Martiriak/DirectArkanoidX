// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Windows_Fixed.h"
#include <d3d11.h>
#include <wrl.h>


class Renderer
{
public:

	Renderer(HWND h_window);
	Renderer(const Renderer&) = delete;
	Renderer& operator= (const Renderer&) = delete;
	~Renderer() = default;

	void present();

	inline void clearBuffer(float rgb) { clearBuffer(rgb, rgb, rgb); }
	void clearBuffer(float red, float green, float blue);

private:

	Microsoft::WRL::ComPtr<ID3D11Device> _device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> _device_context;
	Microsoft::WRL::ComPtr<IDXGISwapChain> _swap_chain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _render_target_view;
};
