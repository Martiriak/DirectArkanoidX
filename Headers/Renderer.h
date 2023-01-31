// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Windows_Fixed.h"
#include "ChiliException.h"
#include <d3d11.h>
#include <wrl.h>


/**
 * Main access point to DirectX 11 objects and functions. It renders onto a H_WND, which is usually provided by a Window class.
 * 
 * Provides a method to draw whatever was set on the device context, using the indices method, and a method to do the presentation and switch buffers.
 * It hides all the DirectX device and device context initializations.
 * 
 * @see Window
 */
class Renderer
{
	friend class IBindable;

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
	void drawIndexed(UINT indices_count) noexcept;

	inline void clearBuffer(float rgb) { clearBuffer(rgb, rgb, rgb); }
	void clearBuffer(float red, float green, float blue);

private:

	Microsoft::WRL::ComPtr<ID3D11Device> _device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> _device_context;
	Microsoft::WRL::ComPtr<IDXGISwapChain> _swap_chain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _render_target_view;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depth_view;
};
