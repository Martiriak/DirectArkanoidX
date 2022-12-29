// Alessandro Pegoraro - Graphics Programming

#pragma once

#include <bitset>


class Keyboard final
{
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
