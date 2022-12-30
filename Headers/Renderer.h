// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Windows_Fixed.h"
#include <d3d11.h>


class Renderer
{
public:

	Renderer(HWND h_window);
	Renderer(const Renderer&) = delete;
	Renderer& operator= (const Renderer&) = delete;
	~Renderer();

	void present();

	inline void clearBuffer(float rgb) { clearBuffer(rgb, rgb, rgb); }
	void clearBuffer(float red, float green, float blue);

private:

	ID3D11Device* _device = nullptr;
	ID3D11DeviceContext* _device_context = nullptr;
	IDXGISwapChain* _swap_chain = nullptr;
	ID3D11RenderTargetView* _render_target_view = nullptr;
};
