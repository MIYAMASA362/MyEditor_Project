#pragma once
#ifndef CORE_MATRIX_H
#define CORE_MATRIX_H

namespace Core
{
	struct Matrix3x3
	{
		union
		{
			float m[3][3];
			struct
			{
				float _00, _01, _02;
				float _10, _11, _12;
				float _20, _21, _22;
			};
		};

		Matrix3x3() = default;
		constexpr Matrix3x3(
			float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22)
			:
			_00(m00), _01(m01), _02(m02),
			_10(m10), _11(m11), _12(m12),
			_20(m20), _21(m21), _22(m22) {}

		float	operator() (size_t row, size_t column) const { return m[row][column]; }
		float& operator() (size_t row, size_t column) { return m[row][column]; }

		Matrix3x3& operator= (const Matrix3x3& matrix);
	};

	struct Matrix4x3
	{
		union
		{
			float m[4][3];
			struct
			{
				float _00, _01, _02;
				float _10, _11, _12;
				float _20, _21, _22;
				float _30, _31, _32;
			};
		};

		Matrix4x3() = default;
		constexpr Matrix4x3(
			float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22,
			float m30, float m31, float m32)
			:
			_00(m00), _01(m00), _02(m02),
			_10(m10), _11(m11), _12(m12),
			_20(m20), _21(m21), _22(m22),
			_30(m30), _31(m31), _32(m32) {}

		float operator() (size_t row, size_t column) const { return m[row][column]; }
		float& operator() (size_t row, size_t column) { return m[row][column]; }

		Matrix4x3& operator= (const Matrix4x3& matrix);
	};

	struct Matrix4x4
	{
		union
		{
			float m[4][4];
			struct
			{
				float _00, _01, _02, _03;
				float _10, _11, _12, _13;
				float _20, _21, _22, _23;
				float _30, _31, _32, _33;
			};
		};

		Matrix4x4() = default;
		constexpr Matrix4x4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33)
			:
			_00(m00), _01(m01), _02(m02), _03(m03),
			_10(m10), _11(m11), _12(m12), _13(m13),
			_20(m20), _21(m21), _22(m22), _23(m23),
			_30(m30), _31(m31), _32(m32), _33(m33) {}

		float operator() (size_t row, size_t column) const { return m[row][column]; }
		float& operator() (size_t row, size_t column) { return m[row][column]; }

		Matrix4x4& operator= (const Matrix4x4& matrix);
	};

}// namespace Core

#endif // ifndef CORE_MATRIX_H