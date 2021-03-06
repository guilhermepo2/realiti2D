#pragma once
#include "Component.h"
#include "Realiti2D/Math/Math.h"

namespace Realiti2D {
	class Transform : public Component {
	public:
		Vector2 Position;
		float Rotation;
		Vector2 Scale;

		Transform() {}

		Transform(const Vector2& InPosition, const float& InRotation, const Vector2& InScale) {
			Position = InPosition;
			Rotation = InRotation;
			Scale = InScale;
		}

		void Translate(Vector2& DeltaMovement) {
			Position += DeltaMovement;
		}

		void ChangeScaleXSign(int Sign) {
			Scale.x = Sign * Math::Abs(Scale.x);
		}
	};
}