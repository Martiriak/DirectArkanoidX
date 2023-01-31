// Alessandro Pegoraro - Graphics Programming

#pragma once

#include "Renderer.h"
#include <DirectXMath.h>
#include <memory>
#include <vector>
#include "Bindables/ConstantBuffers.h"
#include "Vector2.h"


class IBindable;

/**
 * Base class for all entities with a position in the world and that can be drawn by DirectX.
 * 
 * It keeps a vector of IBindable objects, and pointers to an IndexBuffer and a VertexConstantBuffer for convenience reasons.
 * 
 * @see IBindable
 */
class Drawable
{
	template <typename T> friend class DrawableStatics;

public:

	Vector2 position;
	Vector2 velocity;


	Drawable() = default;
	Drawable(const Drawable&) = delete;
	virtual ~Drawable() = default;

	/**
	 * First it binds all the IBindables it owns, then issues a draw command to the Renderer.
	 */
	void draw(Renderer& renderer) const noexcept;

	void addBind(std::unique_ptr<IBindable> new_bind) noexcept;
	void setIndexBuffer(std::unique_ptr<class IndexBuffer> index_buffer) noexcept;

	DirectX::XMMATRIX getTransformMatrix() const noexcept;

	inline void updatePositionUsingVelocity(float delta_time) noexcept { position = position + (velocity * delta_time); }

	virtual void handleCollision(Vector2 surface_normal) noexcept = 0;

protected:

	/**
	 * Gets the vector if IBindables that are not owned directly by an instance of this class, but rather statically.
	 * 
	 * @see DrawableStatics
	 */
	virtual const std::vector<std::unique_ptr<IBindable>>& getStaticBinds() const noexcept = 0;

private:

	const class IndexBuffer* _index_buffer = nullptr;
	mutable std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> _transform_constant_buffer;
	std::vector<std::unique_ptr<IBindable>> _binds;

	void updateAndBindTransformConstantBuffer(Renderer& renderer) const;
};
