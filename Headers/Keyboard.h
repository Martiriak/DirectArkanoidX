// Alessandro Pegoraro - Graphics Programming

#pragma once

#include <bitset>


/**
 * Provides an easy querying system for user input using a bitset, simplifying Win32 input handling.
 * 
 * Each time a key is pressed, a corresponding bit is set to true and each time it is release, the bit is set to false.
 * Each key has a unique bit, accessible through its ASCII code.
 */
class Keyboard final
{
	// Only Window can access its private methods and thus set the bits.
	friend class Window;

public:

	Keyboard() = default;

	Keyboard(const Keyboard&) = delete;
	Keyboard(Keyboard&&) = delete;
	Keyboard& operator= (const Keyboard&) = delete;
	Keyboard& operator= (Keyboard&&) = delete;

	bool isKeyPressed(unsigned char key_code) const noexcept;

private:

	static constexpr unsigned int _keys_number = 256u;

	std::bitset<_keys_number> _keys_states;

	void setKeyPressed(unsigned char key_code) noexcept;
	void setKeyReleased(unsigned char key_code) noexcept;

	void clearKeysStates() noexcept;
};
