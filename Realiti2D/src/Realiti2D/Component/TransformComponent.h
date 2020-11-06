#pragma once
#include "Component.h"
#include "Realiti2D/Math/Math.h"

namespace Realiti2D {
	class Transform : public Component {
	public:
		Vector2 Position;
		Quaternion Rotation;
		Vector2 Scale;

		Transform() {}

		Transform(const Vector2& InPosition, const Quaternion& InRotation, const Vector2& InScale) {
			Position = InPosition;
			Rotation = InRotation;
			Scale = InScale;
		}
	};
}