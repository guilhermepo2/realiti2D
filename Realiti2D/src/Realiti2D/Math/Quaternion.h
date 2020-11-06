#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Realiti2D {
	class Quaternion {
	public:
		glm::quat Q;

		Quaternion() {
			*this = Quaternion::Identity;
		}

		// oh damn this is bad
		// Quaternions can be (x, y, z, w) or (w, x, y, z)
		// 	┏┓
		// 	┃┃╱╲ in
		// 	┃╱╱╲╲ this
		// 	╱╱╭╮╲╲ engine
		// 	▔▏┗┛▕▔ we
		// 	╱▔▔▔▔▔▔▔▔▔▔╲
		// 	use (x, y, z, w)
		//  ╱╱┏┳┓╭╮┏┳┓ ╲╲
		// 	▔▏┗┻┛┃┃┗┻┛▕▔
		explicit Quaternion(float InX, float InY, float InZ, float InW) {
			Q = glm::quat(InW, InX, InY, InZ);
		}

	public:
		static const Quaternion Identity;
	};
}