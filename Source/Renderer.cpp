// Alessandro Pegoraro - Graphics Programming

#include "Renderer.h"
#include "DXErr/dxerr.h"
#include <sstream>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

#define THROW_IF_FAILED(hrCall) if (FAILED(h_result = (hrCall))) throw Renderer::Exception(__LINE__, __FILE__, h_result)
#define MAKE_DEVICE_REMOVED_EXCEPTION(h_result) Renderer::DeviceRemovedException(__LINE__, __FILE__, (h_result))


namespace wrl = Microsoft::WRL;

Renderer::Renderer(HWND h_window)
{
	HRESULT h_result;

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


	THROW_IF_FAILED(D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
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
}


void Renderer::clearBuffer(float red, float green, float blue)
{
	const float color[] = { red, green, blue, 1.f };

	_device_context->ClearRenderTargetView(_render_target_view.Get(), color);
}



void Renderer::tryStuff()
{
	using byte = unsigned char;
	using uint16 = unsigned short;

	HRESULT h_result;

	struct Vertex { float x, y; byte r, g, b, a; };

	const Vertex vertices[] =
	{
		{ 0.f, 0.5f, 255u, 0u, 0u, 0u },
		{ 0.5f, -0.5f, 0u, 255u, 0u, 0u },
		{ -0.5f, -0.5f, 0u, 0u, 255u, 0u },
	};

	// SHADER SETTING

	wrl::ComPtr<ID3DBlob> binary_data;

	wrl::ComPtr<ID3D11PixelShader> pixel_shader;
	THROW_IF_FAILED(D3DReadFileToBlob(L"Shaders\\PixelShader.cso", &binary_data));
	THROW_IF_FAILED(_device->CreatePixelShader(binary_data->GetBufferPointer(), binary_data->GetBufferSize(), nullptr, &pixel_shader));

	_device_context->PSSetShader(pixel_shader.Get(), nullptr, 0u);

	wrl::ComPtr<ID3D11VertexShader> vertex_shader;
	THROW_IF_FAILED(D3DReadFileToBlob(L"Shaders\\VertexShader.cso", &binary_data));
	THROW_IF_FAILED(_device->CreateVertexShader(binary_data->GetBufferPointer(), binary_data->GetBufferSize(), nullptr, &vertex_shader));

	_device_context->VSSetShader(vertex_shader.Get(), nullptr, 0u);

	// VERTEX BUFFER

	wrl::ComPtr<ID3D11Buffer> vertex_buffer;
	D3D11_BUFFER_DESC vertex_descriptor = { 0 };
	vertex_descriptor.BindFlags            = D3D11_BIND_VERTEX_BUFFER;
	vertex_descriptor.Usage                = D3D11_USAGE_DEFAULT;
	vertex_descriptor.CPUAccessFlags       = 0u;
	vertex_descriptor.MiscFlags            = 0u;
	vertex_descriptor.ByteWidth            = sizeof(vertices);
	vertex_descriptor.StructureByteStride  = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA vertex_buffer_subresource = { 0 };
	vertex_buffer_subresource.pSysMem = vertices;

	THROW_IF_FAILED(_device->CreateBuffer(&vertex_descriptor, &vertex_buffer_subresource, &vertex_buffer));

	constexpr UINT stride = sizeof(Vertex);
	constexpr UINT offset = 0u;
	_device_context->IASetVertexBuffers(0u, 1u, vertex_buffer.GetAddressOf(), &stride, &offset);

	// INPUT LAYOUT

	wrl::ComPtr<ID3D11InputLayout> input_layout;

	const D3D11_INPUT_ELEMENT_DESC input_element_descriptors[] =
	{
		{ "Position", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ "Color", 0u, DXGI_FORMAT_R8G8B8A8_UNORM, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u }
	};

	THROW_IF_FAILED(_device->CreateInputLayout
	(
		input_element_descriptors,
		(UINT) (sizeof(input_element_descriptors) / sizeof(D3D11_INPUT_ELEMENT_DESC)),
		binary_data->GetBufferPointer(),
		binary_data->GetBufferSize(),
		&input_layout
	));

	_device_context->IASetInputLayout(input_layout.Get());

	// SOME CONTEXT SETTINGS

	_device_context->OMSetRenderTargets(1u, _render_target_view.GetAddressOf(), nullptr);
	_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// VIEWPORT CONFIG

	D3D11_VIEWPORT viewport = { 0 };
	viewport.Width     = 800.f;
	viewport.Height    = 600.f;
	viewport.MinDepth  = 0.f;
	viewport.MaxDepth  = 1.f;
	viewport.TopLeftX  = 0.f;
	viewport.TopLeftY  = 0.f;

	_device_context->RSSetViewports(1u, &viewport);

	// DRAW!

	_device_context->Draw((UINT) (sizeof(vertices) / sizeof(Vertex)), 0u);
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
