// Alessandro Pegoraro - Graphics Programming

#pragma once


#define THROW_IF_FAILED(hrCall) if (FAILED(h_result = (hrCall))) throw Renderer::Exception(__LINE__, __FILE__, h_result)
#define MAKE_DEVICE_REMOVED_EXCEPTION(h_result) Renderer::DeviceRemovedException(__LINE__, __FILE__, (h_result))
