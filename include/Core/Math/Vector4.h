#pragma once
#ifndef CORE_VECTOR3_H
#define CORE_VECTOR3_H

namespace Core
{
	struct Vector4
	{
		union
		{
			float f[4];
			struct { float x, y, z, w; };
		};

		Vector4() = default;
		constexpr Vector4(float _x, float _y, float _z, float _w) :x(_x), y(_y), z(_z), w(_w) {}

		inline operator const float* () const { return f; }
		Vector4& operator= (const Vector4& vec) { x = vec.x; y = vec.y; z = vec.z; w = vec.w; return *this; }
	};// struct Vector4

}// namespace Core

#endif // ifndef CORE_VECTOR3_H