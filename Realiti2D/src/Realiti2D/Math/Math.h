#pragma once

// The Math Module is basically just syntatic sugar for glm.

#include <glm/glm.hpp>
#include "Vector2.h"
#include "Matrix4.h"
#include "Quaternion.h"

namespace Realiti2D::Math {
	template<typename T>
	T Max(const T& A, const T& B) {
		return glm::max(A, B);
	}

	template<typename T>
	T Min(const T& A, const T& B) {
		return glm::min(A, B);
	}

	template<typename T>
	T Clamp(const T& Value, const T& Lower, const T& Upper) {
		return glm::clamp(Value, Lower, Upper);
	}
}