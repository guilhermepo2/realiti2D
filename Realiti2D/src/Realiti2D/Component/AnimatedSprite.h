#pragma once
#include "Component.h"
#include "Sprite.h"

namespace Realiti2D {
	class AnimatedSprite : public Component {
	public:
		AnimatedSprite() {
			m_CurrentFrame = 0;
			m_AnimationFPS = 24.0f; // default fps (bad)
		}

		void BeginPlay() override {
			m_SpriteReference = Owner->GetComponentOfType<Sprite>();
		}

		void Update(float DeltaTime) override {
			if (m_AnimationTextures.size() > 0) {
				// CORE_INFO("updating animted sprite");
				m_CurrentFrame += (m_AnimationFPS * DeltaTime);

				while (m_CurrentFrame >= m_AnimationTextures.size()) {
					m_CurrentFrame -= m_AnimationTextures.size();
				}

				// CORE_INFO("Current Frame: {0} - Animation FPS: {1}", m_CurrentFrame, m_AnimationFPS);
				// CORE_INFO("Current Frame INT: {0}", static_cast<int>(m_CurrentFrame));
				m_SpriteReference->SetTexture(m_AnimationTextures[static_cast<int>(m_CurrentFrame)]);
			}
		}

		inline void SetAnimationFPS(float _fps) { m_AnimationFPS = _fps; }
		inline void AddAnimationTexture(std::string _TexturePath) {
			CORE_INFO("Adding texture {0} to animated sprite", _TexturePath);
			m_AnimationTextures.push_back(Renderer::s_Instance->GetTexture(_TexturePath));
		}

	private:
		Sprite* m_SpriteReference;
		std::vector<Texture*> m_AnimationTextures;
		float m_CurrentFrame;
		float m_AnimationFPS;

	};
}