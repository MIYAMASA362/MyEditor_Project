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

		Quaternion() : Quaternion(0.0f,0.0f,0.0f,1.0f){}
		constexpr Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

		inline operator const float* () const { return f; }

		Quaternion& operator= (const Quaternion& q) { x = q.x; y = q.y; z = q.z; w = q.w; return *this; }

		static Quaternion identity() { return Quaternion(0.0f,0.0f,0.0f,1.0f); }
	};

}// namespace Core

#endif