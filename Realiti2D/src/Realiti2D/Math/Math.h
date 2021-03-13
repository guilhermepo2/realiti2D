#pragma once

// The Math Module is basically just syntatic sugar for glm.

#include <glm/glm.hpp>
#include <limits>
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

	template<typename T>
	T Abs(const T& Value) {
		return glm::abs(Value);
	}

	template<typename T>
	T Sign(const T& Value) {
		return glm::sign(Value);
	}

	template<typename T>
	T Sin(const T& Value) {
		return glm::sin(Value);
	}

	template<typename T>
	T Cos(const T& Value) {
		return glm::cos(Value);
	}

	const static float FloatInfinity = std::numeric_limits<float>::max();
}