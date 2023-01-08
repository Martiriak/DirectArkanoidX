// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Windows_Fixed.h"
#include "ChiliException.h"
#include <d3d11.h>
#include <wrl.h>


class Renderer
{
//// INNER CLASSES ////

public:

	class Exception : public ChiliException
	{
	public:

		Exception(int line, const char* file, HRESULT h_result) noexcept;

		HRESULT getErrorCode() const noexcept;
		std::string getErrorString() const noexcept;
		std::string getErrorDescription() const noexcept;

		const char* what() const noexcept override;
		const char* GetType() const noexcept override;

	private:

		HRESULT _h_result;
	};

	class DeviceRemovedException : public Exception
	{
		using Exception::Exception;

	public:

		const char* GetType() const noexcept override;
	};


//// MEMBERS ////

public:

	Renderer(HWND h_window);
	Renderer(const Renderer&) = delete;
	Renderer& operator= (const Renderer&) = delete;
	~Renderer() = default;

	void present();

	inline void clearBuffer(float rgb) { clearBuffer(rgb, rgb, rgb); }
	void clearBuffer(float red, float green, float blue);

	void tryStuff(float delta_time);

private:

	Microsoft::WRL::ComPtr<ID3D11Device> _device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> _device_context;
	Microsoft::WRL::ComPtr<IDXGISwapChain> _swap_chain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _render_target_view;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depth_view;
};
