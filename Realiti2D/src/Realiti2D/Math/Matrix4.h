#pragma once
#include <memory.h>
#include <glm/glm.hpp>
#include "glm/gtc/quaternion.hpp"

namespace Realiti2D {

	class Quaternion;

	class Matrix4 {
	public:
		glm::mat4 M;

		Matrix4() { M = glm::mat4(1.0f); }
		Matrix4(glm::mat4 InM) { M = InM; } // TODO: this should be a memcpy?

	public:
		const float* GetAsFloatPointer() const { return reinterpret_cast<const float*>(&M[0][0]); }

	public:
		
		static Matrix4 CreateSimpleViewProj(float Width, float Height) {
			glm::mat4 T =
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
			glm::mat4 T =
			{
				{ xScale, 0.0f, 0.0f, 0.0f },
				{ 0.0f, yScale, 0.0f, 0.0f },
				{ 0.0f, 0.0f, zScale, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 1.0f }
			};

			return Matrix4(T);
		}

		static Matrix4 CreateFromQuaternion(const glm::quat& q);
		static Matrix4 CreateFromQuaternion(const Quaternion& q);

		static Matrix4 CreateTranslation(float x, float y, float z)
		{
			glm::mat4 T =
			{
				{ 1.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 1.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 1.0f, 0.0f },
				{ x, y, z, 1.0f }
			};
			return Matrix4(T);
		}

	public:
		friend Matrix4 operator*(const Matrix4& a, const Matrix4& b)
		{
			Matrix4 retVal;
			retVal.M = (a.M * b.M);
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