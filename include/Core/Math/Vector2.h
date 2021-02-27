#pragma once
#ifndef CORE_VECTOR2_H
#define CORE_VECTOR2_H

namespace Core
{
	struct Vector2
	{
		union
		{
			float f[2];
			struct { float x, y; };
		};

		Vector2() : Vector2(0.0f, 0.0f) {}
		constexpr Vector2(float _x, float _y) : x(_x), y(_y) {}

		inline operator const float* () const { return f; }

		Vector2& operator= (const Vector2& vec) { x = vec.x; y = vec.y; return *this; }
	};// struct Vector2

}// namespace Core

#endif // ifndef CORE_VECTOR2_H
