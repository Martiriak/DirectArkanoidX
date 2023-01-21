// Alessandro Pegoraro - Graphics Programming

#include "Drawables/Drawable.h"
#include "Bindables/Bindable.h"
#include "Bindables/IndexBuffer.h"
#include <cassert>
#include <typeinfo>


void Drawable::draw(Renderer& renderer) const noexcept
{
	updateAndBindTransformConstantBuffer(renderer);

	for (auto& bound : _binds)
	{
		bound->bindTo(renderer);
	}

	for (auto& static_bound : getStaticBinds())
	{
		static_bound->bindTo(renderer);
	}

	renderer.drawIndexed(_index_buffer->getIndicesNumber());
}

void Drawable::addBind(std::unique_ptr<IBindable> new_bind) noexcept
{
	assert("Use function \'setIndexBuffer\' to bind a IndexBuffer." && (typeid(*new_bind) != typeid(IndexBuffer)));

	_binds.push_back(std::move(new_bind));
}

void Drawable::setIndexBuffer(std::unique_ptr<IndexBuffer> index_buffer) noexcept
{
	assert("Attempted to bind a IndexBuffer for the second time." && _index_buffer == nullptr);

	_index_buffer = index_buffer.get();
	_binds.push_back(std::move(index_buffer));
}

DirectX::XMMATRIX Drawable::getTransformMatrix() const noexcept
{
	return DirectX::XMMatrixTranslation(position.x, position.y, 0.f);
}

void Drawable::updateAndBindTransformConstantBuffer(Renderer& renderer) const
{
	DirectX::XMMATRIX transform = DirectX::XMMatrixTranspose(getTransformMatrix());

	if (_transform_constant_buffer) _transform_constant_buffer->updateElements(renderer, transform);
	else
	{
		_transform_constant_buffer =
			std::make_unique<VertexConstantBuffer<DirectX::XMMATRIX>>(renderer, transform);
	}

	_transform_constant_buffer->bindTo(renderer);
}
