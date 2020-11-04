#pragma once
#include <memory.h>

namespace Realiti2D {
	class Matrix4 {
	public:
		float M[4][4];

		Matrix4() {
			*this = Matrix4::Identity;
		}

		explicit Matrix4(float InMat[4][4]) {
			memcpy(M, InMat, 16 * sizeof(float));
		}

	public:
		const float* GetAsFloatPointer() const {
			return reinterpret_cast<const float*>(&M[0][0]);
		}

	public:
		
		static Matrix4 CreateSimpleViewProj(float Width, float Height) {
			float T[4][4] =
			{
				{ 2.0f / Width, 0.0f,			0.0f, 0.0f },
				{ 0.0f,			2.0f / Height,	0.0f, 0.0f },
				{ 0.0f,			0.0f,			1.0f, 0.0f },
				{ 0.0f,			0.0f,			1.0f, 1.0f }
			};

			return Matrix4(T);
		}

		static Matrix4 CreateScale(float xScale, float yScale, float zScale)
		{
			float T[4][4] =
			{
				{ xScale, 0.0f, 0.0f, 0.0f },
				{ 0.0f, yScale, 0.0f, 0.0f },
				{ 0.0f, 0.0f, zScale, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 1.0f }
			};

			return Matrix4(T);
		}

		static Matrix4 CreateFromQuaternion(const class Quaternion& q);

		static Matrix4 CreateTranslation(float x, float y, float z)
		{
			float temp[4][4] =
			{
				{ 1.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 1.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 1.0f, 0.0f },
				{ x, y, z, 1.0f }
			};
			return Matrix4(temp);
		}

	public:
		// Matrix multiplication (a * b)
		friend Matrix4 operator*(const Matrix4& a, const Matrix4& b)
		{
			Matrix4 retVal;
			// row 0
			retVal.M[0][0] =
				a.M[0][0] * b.M[0][0] +
				a.M[0][1] * b.M[1][0] +
				a.M[0][2] * b.M[2][0] +
				a.M[0][3] * b.M[3][0];

			retVal.M[0][1] =
				a.M[0][0] * b.M[0][1] +
				a.M[0][1] * b.M[1][1] +
				a.M[0][2] * b.M[2][1] +
				a.M[0][3] * b.M[3][1];

			retVal.M[0][2] =
				a.M[0][0] * b.M[0][2] +
				a.M[0][1] * b.M[1][2] +
				a.M[0][2] * b.M[2][2] +
				a.M[0][3] * b.M[3][2];

			retVal.M[0][3] =
				a.M[0][0] * b.M[0][3] +
				a.M[0][1] * b.M[1][3] +
				a.M[0][2] * b.M[2][3] +
				a.M[0][3] * b.M[3][3];

			// row 1
			retVal.M[1][0] =
				a.M[1][0] * b.M[0][0] +
				a.M[1][1] * b.M[1][0] +
				a.M[1][2] * b.M[2][0] +
				a.M[1][3] * b.M[3][0];

			retVal.M[1][1] =
				a.M[1][0] * b.M[0][1] +
				a.M[1][1] * b.M[1][1] +
				a.M[1][2] * b.M[2][1] +
				a.M[1][3] * b.M[3][1];

			retVal.M[1][2] =
				a.M[1][0] * b.M[0][2] +
				a.M[1][1] * b.M[1][2] +
				a.M[1][2] * b.M[2][2] +
				a.M[1][3] * b.M[3][2];

			retVal.M[1][3] =
				a.M[1][0] * b.M[0][3] +
				a.M[1][1] * b.M[1][3] +
				a.M[1][2] * b.M[2][3] +
				a.M[1][3] * b.M[3][3];

			// row 2
			retVal.M[2][0] =
				a.M[2][0] * b.M[0][0] +
				a.M[2][1] * b.M[1][0] +
				a.M[2][2] * b.M[2][0] +
				a.M[2][3] * b.M[3][0];

			retVal.M[2][1] =
				a.M[2][0] * b.M[0][1] +
				a.M[2][1] * b.M[1][1] +
				a.M[2][2] * b.M[2][1] +
				a.M[2][3] * b.M[3][1];

			retVal.M[2][2] =
				a.M[2][0] * b.M[0][2] +
				a.M[2][1] * b.M[1][2] +
				a.M[2][2] * b.M[2][2] +
				a.M[2][3] * b.M[3][2];

			retVal.M[2][3] =
				a.M[2][0] * b.M[0][3] +
				a.M[2][1] * b.M[1][3] +
				a.M[2][2] * b.M[2][3] +
				a.M[2][3] * b.M[3][3];

			// row 3
			retVal.M[3][0] =
				a.M[3][0] * b.M[0][0] +
				a.M[3][1] * b.M[1][0] +
				a.M[3][2] * b.M[2][0] +
				a.M[3][3] * b.M[3][0];

			retVal.M[3][1] =
				a.M[3][0] * b.M[0][1] +
				a.M[3][1] * b.M[1][1] +
				a.M[3][2] * b.M[2][1] +
				a.M[3][3] * b.M[3][1];

			retVal.M[3][2] =
				a.M[3][0] * b.M[0][2] +
				a.M[3][1] * b.M[1][2] +
				a.M[3][2] * b.M[2][2] +
				a.M[3][3] * b.M[3][2];

			retVal.M[3][3] =
				a.M[3][0] * b.M[0][3] +
				a.M[3][1] * b.M[1][3] +
				a.M[3][2] * b.M[2][3] +
				a.M[3][3] * b.M[3][3];

			return retVal;
		}

		Matrix4& operator*=(const Matrix4& right)
		{
			*this = *this * right;
			return *this;
		}

		public:
		static const Matrix4 Identity;
	};
}