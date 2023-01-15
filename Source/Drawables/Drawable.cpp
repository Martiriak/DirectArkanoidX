// Alessandro Pegoraro - Graphics Programming

#include "Drawables/Drawable.h"
#include "Bindables/Bindable.h"
#include "Bindables/IndexBuffer.h"
#include <cassert>
#include <typeinfo>


void Drawable::draw(Renderer& renderer) const noexcept
{
	for (auto& bound : _binds)
	{
		bound->bindTo(renderer);
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
