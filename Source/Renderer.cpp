// Alessandro Pegoraro - Graphics Programming

#include "Renderer.h"
#include "DXErr/dxerr.h"
#include <sstream>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

#define THROW_IF_FAILED(hrCall) if (FAILED(h_result = (hrCall))) throw Renderer::Exception(__LINE__, __FILE__, h_result)
#define MAKE_DEVICE_REMOVED_EXCEPTION(h_result) Renderer::DeviceRemovedException(__LINE__, __FILE__, (h_result))


namespace wrl = Microsoft::WRL;

Renderer::Renderer(HWND h_window)
{
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

	// Make Depth Stencil state.
	wrl::ComPtr<ID3D11DepthStencilState> depth_state = nullptr;

	D3D11_DEPTH_STENCIL_DESC depth_state_descriptor = { };
	depth_state_descriptor.DepthEnable     = TRUE;
	depth_state_descriptor.DepthWriteMask  = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_state_descriptor.DepthFunc       = D3D11_COMPARISON_LESS;

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
	_device_context->ClearDepthStencilView(_depth_view.Get(), D3D11_CLEAR_DEPTH, 1.f, 0u);
}



void Renderer::tryStuff(float delta_time)
{
	using byte = unsigned char;
	using uint16 = unsigned short;

	static float time_elapsed = 0.f;

	time_elapsed += delta_time;

	HRESULT h_result;

	struct Vertex { float x, y; byte r, g, b, a; };

	struct RotationMatrix { DirectX::XMMATRIX transform; };

	const Vertex vertices[] =
	{
		{ 0.f, 0.75f, 255u, 0u, 0u, 0u },
		{ 0.25f, 0.25f, 0u, 255u, 0u, 0u },
		{ 0.75f, 0.f, 0u, 0u, 255u, 0u },
		{ 0.25f, -0.25f, 0u, 255u, 255u, 0u },
		{ 0.f, -0.75f, 255u, 0u, 255u, 0u },
		{ -0.25f, -0.25f, 255u, 255u, 0u, 0u },
		{ -0.75f, 0.f, 255u, 255u, 255u, 0u },
		{ -0.25f, 0.25f, 0u, 0u, 0u, 0u },
	};

	const uint16 indices[] =
	{
		7, 0, 1,
		1, 2, 3,
		3, 4, 5,
		5, 6, 7,
		7, 1, 5,
		5, 1, 3
	};

	const RotationMatrix matrices[] =
	{
		{ DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationZ(time_elapsed)) }
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
	D3D11_BUFFER_DESC vertex_descriptor = { };
	vertex_descriptor.BindFlags            = D3D11_BIND_VERTEX_BUFFER;
	vertex_descriptor.Usage                = D3D11_USAGE_DEFAULT;
	vertex_descriptor.CPUAccessFlags       = 0u;
	vertex_descriptor.MiscFlags            = 0u;
	vertex_descriptor.ByteWidth            = sizeof(vertices);
	vertex_descriptor.StructureByteStride  = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA vertex_buffer_subresource = { };
	vertex_buffer_subresource.pSysMem = vertices;

	THROW_IF_FAILED(_device->CreateBuffer(&vertex_descriptor, &vertex_buffer_subresource, &vertex_buffer));

	constexpr UINT vertex_stride = sizeof(Vertex);
	constexpr UINT vertex_offset = 0u;
	_device_context->IASetVertexBuffers(0u, 1u, vertex_buffer.GetAddressOf(), &vertex_stride, &vertex_offset);

	// INDEX BUFFER

	wrl::ComPtr<ID3D11Buffer> index_buffer;
	D3D11_BUFFER_DESC index_descriptor = { };
	index_descriptor.BindFlags            = D3D11_BIND_INDEX_BUFFER;
	index_descriptor.Usage                = D3D11_USAGE_DEFAULT;
	index_descriptor.CPUAccessFlags       = 0u;
	index_descriptor.MiscFlags            = 0u;
	index_descriptor.ByteWidth            = sizeof(indices);
	index_descriptor.StructureByteStride  = sizeof(uint16);

	D3D11_SUBRESOURCE_DATA index_buffer_subresource = { };
	index_buffer_subresource.pSysMem = indices;

	THROW_IF_FAILED(_device->CreateBuffer(&index_descriptor, &index_buffer_subresource, &index_buffer));

	constexpr UINT index_offset = 0u;
	_device_context->IASetIndexBuffer(index_buffer.Get(), DXGI_FORMAT_R16_UINT, index_offset);

	// CONSTANT BUFFER

	wrl::ComPtr<ID3D11Buffer> constant_buffer;
	D3D11_BUFFER_DESC constant_descriptor = { };
	constant_descriptor.BindFlags            = D3D11_BIND_CONSTANT_BUFFER;
	constant_descriptor.Usage                = D3D11_USAGE_DYNAMIC;
	constant_descriptor.CPUAccessFlags       = D3D11_CPU_ACCESS_WRITE;
	constant_descriptor.MiscFlags            = 0u;
	constant_descriptor.ByteWidth            = sizeof(matrices);
	constant_descriptor.StructureByteStride  = sizeof(RotationMatrix);

	D3D11_SUBRESOURCE_DATA constant_buffer_subresource = { };
	constant_buffer_subresource.pSysMem = matrices;

	THROW_IF_FAILED(_device->CreateBuffer(&constant_descriptor, &constant_buffer_subresource, &constant_buffer));

	_device_context->VSSetConstantBuffers(0u, 1u, constant_buffer.GetAddressOf());

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

	D3D11_VIEWPORT viewport = { };
	viewport.Width     = 800.f;
	viewport.Height    = 800.f;
	viewport.MinDepth  = 0.f;
	viewport.MaxDepth  = 1.f;
	viewport.TopLeftX  = 0.f;
	viewport.TopLeftY  = 0.f;

	_device_context->RSSetViewports(1u, &viewport);

	// DRAW!

	//_device_context->Draw((UINT)(sizeof(vertices) / sizeof(Vertex)), 0u);
	_device_context->DrawIndexed((UINT)(sizeof(indices) / sizeof(uint16)), 0u, 0u);
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
