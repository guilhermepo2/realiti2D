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

		const float* GetAsFloatPointer() const {
			return reinterpret_cast<const float*>(&M[0][0]);
		}

	public:
		static const Matrix4 Identity;
	};
}