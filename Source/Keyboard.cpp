// Alessandro Pegoraro - Graphics Programming

#include "Keyboard.h"


bool Keyboard::isKeyPressed(unsigned char key_code) const noexcept
{
	return _keys_states[key_code];
}

void Keyboard::setKeyPressed(unsigned char key_code) noexcept
{
	_keys_states.set(key_code, true);
}

void Keyboard::setKeyReleased(unsigned char key_code) noexcept
{
	_keys_states.set(key_code, false);
}

void Keyboard::clearKeysStates() noexcept
{
	_keys_states.reset();
}
