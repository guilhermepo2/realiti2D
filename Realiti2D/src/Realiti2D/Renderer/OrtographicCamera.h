#pragma once
#include "Color.h"
#include "glm/glm.hpp"
#include "Realiti2D/Math/Math.h"

namespace Realiti2D {
	class OrtographicCamera {
	public:
		OrtographicCamera(float Width, float Height) : m_CameraBackgroundColor(0.0f, 0.0f,  1.0f, 1.0f) {
			m_CameraProjection = glm::ortho(
				-(Width / 2.0f), (Width / 2.0f),
				-(Height / 2.0f), (Height / 2.0f),
				-10.0f, 10.0f
			);

			m_CameraTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 10.0f));

			m_CameraView = glm::inverse(m_CameraTransform);
		}

		glm::mat4 GetCameraViewProjection() {
			return m_CameraProjection * m_CameraView;
		}

		void SetBackgroundColor(float _r, float _g, float _b, float _a) {
			m_CameraBackgroundColor.rgba[0] = _r;
			m_CameraBackgroundColor.rgba[1] = _g;
			m_CameraBackgroundColor.rgba[2] = _b;
			m_CameraBackgroundColor.rgba[3] = _a;
		}

		inline float R() const { return m_CameraBackgroundColor.rgba[0]; }
		inline float G() const { return m_CameraBackgroundColor.rgba[1]; }
		inline float B() const { return m_CameraBackgroundColor.rgba[2]; }
		inline float A() const { return m_CameraBackgroundColor.rgba[3]; }

	private:
		Color m_CameraBackgroundColor;
		glm::mat4 m_CameraProjection;
		glm::mat4 m_CameraTransform;
		glm::mat4 m_CameraView;
	};
}