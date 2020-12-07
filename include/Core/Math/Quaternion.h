#pragma once
#ifndef CORE_QUATERNION_H
#define CORE_QUATERNION_H

namespace Core
{
	struct Quaternion
	{
		union
		{
			float f[4];
			struct { float x, y, z, w; };
		};

		Quaternion() = default;
		constexpr Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

		inline operator const float* () const { return f; }

		Quaternion& operator= (const Quaternion& q) { x = q.x; y = q.y; z = q.z; w = q.w; return *this; }
	};

}// namespace Core

#endif