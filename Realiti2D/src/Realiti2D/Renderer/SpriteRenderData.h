#pragma once

namespace Realiti2D {

	class Vector3;
	class Quaternion;
	class Texture;

	struct SpriteRenderData {
		Texture* Texture;
		Vector3* Position;
		Quaternion* Rotation;
		Vector3* Scale;
	};
}