#pragma once

namespace Realiti2D {

	class Vector2;
	class Texture;
	class Color;

	struct SpriteRenderData {
		Texture* Texture;
		Vector2* Position;
		float Rotation;
		Vector2* Scale;
		int DrawOrder;
		Color* _Color;

		float Width;
		float Height;
	};
}