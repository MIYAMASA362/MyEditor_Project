#pragma once
#ifndef CORE_VECTOR3_H
#define CORE_VECTOR3_H

namespace Core
{
	struct Vector3
	{
		union
		{
			float f[3];
			struct { float x, y, z; };
		};

		Vector3() : Vector3(0.0f, 0.0f, 0.0f) {};
		constexpr Vector3(float _x, float _y, float _z) :x(_x), y(_y), z(_z) {}

		inline operator const float* () const { return f; }

		Vector3& operator= (const Vector3& vec) { x = vec.x; y = vec.y; z = vec.z; }
	};// struct Vector3

}// namespace Core

#endif // ifndef CORE_VECTOR3_H