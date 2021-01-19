#pragma once

namespace Realiti2D {
	class Color {
	public:
		float rgba[4];

		Color(float _r, float _g, float _b, float _a) {
			rgba[0] = _r;
			rgba[1] = _g;
			rgba[2] = _b;
			rgba[3] = _a;
		}
	};
}