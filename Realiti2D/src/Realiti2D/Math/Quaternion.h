#pragma once

namespace Realiti2D {
	class Quaternion {
	public:
		float x;
		float y;
		float z;
		float w;

		Quaternion() {
			*this = Quaternion::Identity;
		}

		explicit Quaternion(float InX, float InY, float InZ, float InW) {
			x = InX;
			y = InY;
			z = InZ;
			w = InW;
		}

	public:
		static const Quaternion Identity;
	};
}