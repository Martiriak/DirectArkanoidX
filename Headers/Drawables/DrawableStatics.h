// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Drawables/Drawable.h"
#include "Bindables/IndexBuffer.h"
#include <cassert>
#include <typeinfo>


template <typename DrawableSubclass>
class DrawableStatics : public Drawable
{
protected:

	static bool areStaticsInitialized() noexcept
	{
		return !_static_binds.empty();
	}

	void addStaticBind(std::unique_ptr<IBindable> new_static_bind) noexcept
	{
		assert("Use function \'setStaticIndexBuffer\' to bind a IndexBuffer." && (typeid(*new_static_bind) != typeid(IndexBuffer)));
		_static_binds.push_back(std::move(new_static_bind));
	}

	void setStaticIndexBuffer(std::unique_ptr<IndexBuffer> index_buffer) noexcept
	{
		assert("Attempted to bind a IndexBuffer for the second time." && _index_buffer == nullptr);

		_index_buffer = index_buffer.get();
		_static_binds.push_back(std::move(index_buffer));
	}

	void setIndexFromStatic() noexcept
	{
		assert("Attempted to bind a IndexBuffer for the second time." && _index_buffer == nullptr);
		for (const auto& static_bind : _static_binds)
		{
			if (const auto index_buffer = dynamic_cast<IndexBuffer*>(static_bind.get()))
			{
				_index_buffer = index_buffer;
				return;
			}
		}
		assert("Failed to find a IndexBuffer in static binds." && _index_buffer != nullptr);
	}

private:

	static std::vector<std::unique_ptr<IBindable>> _static_binds;

	const std::vector<std::unique_ptr<IBindable>>& getStaticBinds() const noexcept override final
	{
		return _static_binds;
	}
};


template <typename DrawableSubclass>
std::vector<std::unique_ptr<IBindable>> DrawableStatics<DrawableSubclass>::_static_binds;
