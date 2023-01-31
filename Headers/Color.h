// Alessandro Pegoraro - Graphics Programming

#pragma once


using byte = unsigned char;

/**
 * Simple struct representing a color.
 * 
 * For space optimization reasons, it uses a single byte for each channel, instead of a float.
 */
struct Color
{
	byte r, g, b, a;


	static inline Color white() { return { 255, 255, 255, 255 }; }
	static inline Color gray() { return { 128, 128, 128, 255 }; }
	static inline Color black() { return { 0, 0, 0, 255 }; }
	static inline Color red() { return { 255, 0, 0, 255 }; }
	static inline Color darkRed() { return { 128, 0, 0, 255 }; }
	static inline Color green() { return { 0, 255, 0, 255 }; }
	static inline Color darkGreen() { return { 0, 128, 0, 255 }; }
	static inline Color blue() { return { 0, 0, 255, 255 }; }
	static inline Color darkBlue() { return { 0, 0, 128, 255 }; }
	static inline Color cyan() { return { 0, 255, 255, 255 }; }
	static inline Color magenta() { return { 255, 0, 255, 255 }; }
	static inline Color yellow() { return { 255, 255, 0, 255 }; }
	static inline Color purple() { return { 128, 0, 128, 255 }; }
	static inline Color orange() { return { 255, 165, 0, 255 }; }

	static Color lerp(const Color& right_side, const Color& left_side, float t);
};
