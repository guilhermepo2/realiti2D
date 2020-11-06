#include "Matrix4.h"
#include "Quaternion.h"

namespace Realiti2D {
	static glm::mat4 m4Ident =
	{
		{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};

	Matrix4 Matrix4::CreateFromQuaternion(const glm::quat& q) {
		glm::mat4 mat = glm::mat4_cast(q);
		return Matrix4(mat);
	}

	Matrix4 Matrix4::CreateFromQuaternion(const Quaternion& q) {
		return CreateFromQuaternion(q.Q);
	}

	const Matrix4 Matrix4::Identity(m4Ident);
}