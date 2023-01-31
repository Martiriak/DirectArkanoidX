# ArkanoidX
This is a C++ DirectX 11 project made from the ground up, for a Graphics Programming course.
The youtube tutorials of *ChiliTomatoNoodle* were taken as inspiration for the architecture and framework developed ([link to the playlist](https://www.youtube.com/watch?v=_4FArgOX1I4&list=PLqCJpWy5Fohd3S7ICFXwUomYW0Wv67pDD)).
This is a very simple 2D Arkanoid-style game, where the objective is to destroy all boxes.

# DirectX
One of the objectives of this project was to abstract DirectX logic from game code as much as possible; this was achieved using the classes `Renderer`, `Drawable` and `IBindable`, and using *COM Smart Pointers* to simplify the management of COM resources.

## Renderer
This class wraps the inizialization of DirectX `device`, `device context` and other general resources like *depth buffer* and *viewport*. It also exposes convinience methods and the draw and present functions for external classes to use.

## Drawable & IBindable
These two classes serves to integrate and abstract DirectX 11 logic with generalized game objects.

### IBindable
This interface abstracts DirectX resources such as shaders, vertex, index and constant buffers, input layouts and so on. Through the use of getter methods, it can access the device and device context from the `Renderer` and use those to initialize itself.

A `IBindable` needs to be bound to the `Renderer` in order to be used. To be bound means that the device context sets that particular resource represented by the `IBindable` class as current.

### Drawable
This class represents an entity with position and velocity that can be drawn by DirectX.
It owns an vector of `IBindables` which binds to the `Renderer` and uses to draw itself.

It possesses two pointers to certain types of resources:
 - A pointer to a `IndexBuffer`, because it needs to know how many indices there are in order to draw.
 - A pointer to a  `VertexConstantBuffer`, because it needs to update it every time it gets drawn to properly reflect its current position.

A `Drawable` also provides the `handleCollision(Vector2 surface_normal)` method, which is called upon a collision and is supplied with the normal of the colliding surface. For example, this method is used by the ball to reflect its velocity vector based on the provided normal.

# Application
The core game loop and structures are wrapped in the `Application` class, which uses a `Window` class to abstract over Win32 API.
This class owns and manages the ball, the paddle and a grid of `DestructibleBoxes` created using configs defined in the `Grid` header.

Every frame, the `Application` class uses a component called `CollisionHandler` to check for collisions, then updates the position of the ball and the paddle based on their velocities, and finally issues the draw command to all of the `Drawables` it manages.

**Keyboard:** This class is a component of the `Window` class, and provides a easy way to know if a particular key is being pressed or not.

## CollisionHandler
This class has 3 tasks:
- Check if the ball collides with any block, and if that's the case, call `handleCollision()` on the colliding `Drawables`, providing the surface normal of the collision.
- Bound the ball to the borders of the screen, preventing it to go out of view.
- Issue a `GameProgress::Won` or `GameProgress::Lost` message when appropriate.


