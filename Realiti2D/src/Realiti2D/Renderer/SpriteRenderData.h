#pragma once

namespace Realiti2D {

	class Vector2;
	class Quaternion;
	class Texture;

	struct SpriteRenderData {
		Texture* Texture;
		Vector2* Position;
		Quaternion* Rotation;
		Vector2* Scale;
	};
}