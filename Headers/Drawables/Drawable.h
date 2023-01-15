// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Renderer.h"
#include <DirectXMath.h>
#include <memory>
#include <vector>


class IBindable;

class Drawable
{

public:

	Drawable() = default;
	Drawable(const Drawable&) = delete;
	virtual ~Drawable() = default;

	void draw(Renderer& renderer) const noexcept;
	void addBind(std::unique_ptr<IBindable> new_bind) noexcept;
	void setIndexBuffer(std::unique_ptr<class IndexBuffer> index_buffer) noexcept;

	virtual DirectX::XMMATRIX getTransformMatrix() const noexcept = 0;
	virtual void update(double total_time_passed, float delta_time) noexcept = 0;

private:

	const class IndexBuffer* _index_buffer = nullptr;
	std::vector<std::unique_ptr<IBindable>> _binds;
};
