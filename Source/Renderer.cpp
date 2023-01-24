// Alessandro Pegoraro - Graphics Programming

#include "Renderer.h"
#include "DXErr/dxerr.h"
#include "DirectXThrowMacros.h"
#include <sstream>
#include <DirectXMath.h>
#include "Drawables/DestructibleBlock.h"
#include "Drawables/Paddle.h"
#include "Drawables/Ball.h"

#pragma comment(lib, "d3d11.lib")


namespace wrl = Microsoft::WRL;

Renderer::Renderer(HWND h_window)
{
#ifndef NDEBUG
	constexpr UINT swap_chain_flags = D3D11_CREATE_DEVICE_DEBUG;
#else
	constexpr UINT swap_chain_flags = 0u;
#endif

	HRESULT h_result;

	DXGI_SWAP_CHAIN_DESC sc_descriptor = { };
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


	THROW_IF_FAILED(D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		swap_chain_flags,
		nullptr,
		0u,
		D3D11_SDK_VERSION,
		&sc_descriptor,
		&_swap_chain,
		&_device,
		nullptr,
		&_device_context
	));

	// Get render_target_view through back buffer COM.
	wrl::ComPtr<ID3D11Resource> back_buffer = nullptr;
	THROW_IF_FAILED(_swap_chain->GetBuffer(0u, __uuidof(ID3D11Resource), &back_buffer));
	THROW_IF_FAILED(_device->CreateRenderTargetView(back_buffer.Get(), nullptr, &_render_target_view));

	// Make Depth Stencil state.
	wrl::ComPtr<ID3D11DepthStencilState> depth_state = nullptr;

	D3D11_DEPTH_STENCIL_DESC depth_state_descriptor = { };
	depth_state_descriptor.DepthEnable     = TRUE;
	depth_state_descriptor.DepthWriteMask  = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_state_descriptor.DepthFunc       = D3D11_COMPARISON_LESS;
	depth_state_descriptor.StencilEnable   = FALSE;


	THROW_IF_FAILED(_device->CreateDepthStencilState(&depth_state_descriptor, &depth_state));

	_device_context->OMSetDepthStencilState(depth_state.Get(), 0u);

	wrl::ComPtr<ID3D11Texture2D> depth_texture = nullptr;

	D3D11_TEXTURE2D_DESC depth_texture_descriptor = { };
	depth_texture_descriptor.Width               = 800u;
	depth_texture_descriptor.Height              = 800u;
	depth_texture_descriptor.MipLevels           = 1u;
	depth_texture_descriptor.ArraySize           = 1u;
	depth_texture_descriptor.Format              = DXGI_FORMAT_D32_FLOAT;
	depth_texture_descriptor.SampleDesc.Count    = 1u;
	depth_texture_descriptor.SampleDesc.Quality  = 0u;
	depth_texture_descriptor.Usage               = D3D11_USAGE_DEFAULT;
	depth_texture_descriptor.BindFlags           = D3D11_BIND_DEPTH_STENCIL;

	THROW_IF_FAILED(_device->CreateTexture2D(&depth_texture_descriptor, nullptr, &depth_texture));

	D3D11_DEPTH_STENCIL_VIEW_DESC depth_view_descriptor = { };
	depth_view_descriptor.Format              = DXGI_FORMAT_UNKNOWN; // It takes that of the texture.
	depth_view_descriptor.ViewDimension       = D3D11_DSV_DIMENSION_TEXTURE2D;
	depth_view_descriptor.Texture2D.MipSlice  = 0u;

	THROW_IF_FAILED(_device->CreateDepthStencilView(depth_texture.Get(), &depth_view_descriptor, &_depth_view));

	_device_context->OMSetRenderTargets(1u, _render_target_view.GetAddressOf(), _depth_view.Get());

	D3D11_VIEWPORT viewport = { };
	viewport.Width     = 800.f;
	viewport.Height    = 800.f;
	viewport.MinDepth  = 0.f;
	viewport.MaxDepth  = 1.f;
	viewport.TopLeftX  = 0.f;
	viewport.TopLeftY  = 0.f;

	_device_context->RSSetViewports(1u, &viewport);
}


void Renderer::present()
{
	HRESULT h_result;

	if (FAILED(h_result = _swap_chain->Present(1u, 0u)))
	{
		if (h_result == DXGI_ERROR_DEVICE_REMOVED)
		{
			throw MAKE_DEVICE_REMOVED_EXCEPTION(_device->GetDeviceRemovedReason());
		}
		else
		{
			throw Renderer::Exception(__LINE__, __FILE__, h_result);
		}
	}

	// DXGI_SWAP_EFFECT_FLIP_DISCARD unbinds the render target, so we must rebound it for the next Present.
	_device_context->OMSetRenderTargets(1u, _render_target_view.GetAddressOf(), _depth_view.Get());
}


void Renderer::drawIndexed(UINT indices_count) noexcept
{
	_device_context->DrawIndexed(indices_count, 0u, 0u);
}

void Renderer::clearBuffer(float red, float green, float blue)
{
	const float color[] = { red, green, blue, 1.f };

	_device_context->ClearRenderTargetView(_render_target_view.Get(), color);
	_device_context->ClearDepthStencilView(_depth_view.Get(), D3D11_CLEAR_DEPTH, 1.f, 0u);
}



void Renderer::tryStuff(float delta_time)
{
	static float time_elapsed = 0.f;

	time_elapsed += delta_time;

	HRESULT h_result;

	static DestructibleBlock quad1(*this, 0.25f, 0.25f, 1.f, 0.75f, { 0, 255, 255, 255 });
	static Paddle quad2(*this, -0.75f, -0.5f, 0.25f, 0.5f, { 255, 0, 0, 255 });

	static Ball circle(*this, 0.f, -0.33f, 0.125f, {0, 130, 0, 255}, {255, 255, 255, 255});

	// UPDATING

	float displacement = 0.001f;
	if ((int) time_elapsed % 2 != 0) displacement = -displacement;

	quad1.position.x += displacement;
	quad2.position.y += displacement;

	// DRAW!

	quad1.draw(*this);
	quad2.draw(*this);
	circle.draw(*this);
}


////// Renderer Exception //////



Renderer::Exception::Exception(int line, const char* file, HRESULT h_result) noexcept
	:
	ChiliException(line, file),
	_h_result(h_result)
{}

const char* Renderer::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] 0x" << std::hex << std::uppercase << getErrorCode()
		<< std::dec << " (" << (unsigned long)getErrorCode() << ")" << std::endl
		<< "[Error String] " << getErrorString() << std::endl
		<< "[Description] " << getErrorDescription() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Renderer::Exception::GetType() const noexcept
{
	return "Chili Graphics Exception";
}

HRESULT Renderer::Exception::getErrorCode() const noexcept
{
	return _h_result;
}

std::string Renderer::Exception::getErrorString() const noexcept
{
	return DXGetErrorString(_h_result);
}

std::string Renderer::Exception::getErrorDescription() const noexcept
{
	char buf[512];
	DXGetErrorDescription(_h_result, buf, sizeof(buf));
	return buf;
}


const char* Renderer::DeviceRemovedException::GetType() const noexcept
{
	return "Renderer Exception [Device Removed] (DXGI_ERROR_DEVICE_REMOVED)";
}
