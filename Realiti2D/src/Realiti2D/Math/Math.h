#pragma once

#include "Vector2.h"
#include "Matrix4.h"
#include "Quaternion.h"

namespace Realiti2D::Math {
	template<typename T>
	T Max(const T& A, const T& B) {
		return (A < B ? B : A);
	}

	template<typename T>
	T Min(const T& A, const T& B) {
		return (A < B ? A : B);
	}

	template<typename T>
	T Clamp(const T& Value, const T& Lower, const T& Upper) {
		return Min(Upper, Max(Lower, Value));
	}
}