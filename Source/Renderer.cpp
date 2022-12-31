// Alessandro Pegoraro - Graphics Programming

#include "Renderer.h"

#pragma comment(lib, "d3d11.lib")


namespace wrl = Microsoft::WRL;

Renderer::Renderer(HWND h_window)
{
	DXGI_SWAP_CHAIN_DESC sc_descriptor = { 0 };
	sc_descriptor.BufferDesc.Width                    = 0u;
	sc_descriptor.BufferDesc.Height                   = 0u;
	sc_descriptor.BufferDesc.Format                   = DXGI_FORMAT_B8G8R8A8_UNORM;
	sc_descriptor.BufferDesc.RefreshRate.Numerator    = 0u;
	sc_descriptor.BufferDesc.RefreshRate.Denominator  = 0u;
	sc_descriptor.BufferDesc.Scaling                  = DXGI_MODE_SCALING_UNSPECIFIED;
	sc_descriptor.BufferDesc.ScanlineOrdering         = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sc_descriptor.SampleDesc.Count                    = 1u;
	sc_descriptor.SampleDesc.Quality                  = 0u;
	sc_descriptor.BufferUsage                         = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sc_descriptor.BufferCount                         = 2u;
	sc_descriptor.OutputWindow                        = h_window;
	sc_descriptor.Windowed                            = TRUE;
	sc_descriptor.SwapEffect                          = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	sc_descriptor.Flags                               = 0u;


	D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0u,
		nullptr,
		0u,
		D3D11_SDK_VERSION,
		&sc_descriptor,
		&_swap_chain,
		&_device,
		nullptr,
		&_device_context
	);

	// Get render_target_view through back buffer COM.
	wrl::ComPtr<ID3D11Resource> back_buffer = nullptr;
	_swap_chain->GetBuffer(0u, __uuidof(ID3D11Resource), &back_buffer);
	_device->CreateRenderTargetView(back_buffer.Get(), nullptr, &_render_target_view);
}


void Renderer::present()
{
	_swap_chain->Present(1u, 0u);
}


void Renderer::clearBuffer(float red, float green, float blue)
{
	const float color[] = { red, green, blue, 1.f };

	_device_context->ClearRenderTargetView(_render_target_view.Get(), color);
}
