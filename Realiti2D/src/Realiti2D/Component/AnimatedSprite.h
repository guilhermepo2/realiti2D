#pragma once
#include "Component.h"
#include "Sprite.h"

namespace Realiti2D {
	struct AnimationClip {
	public:
		std::vector<Texture*> m_AnimationTextures;
		float m_CurrentFrame;
		float m_AnimationFPS;

		AnimationClip() : m_CurrentFrame(0.0f), m_AnimationFPS(24.0f) {}
		AnimationClip(float _fps) : m_CurrentFrame(0.0f), m_AnimationFPS(_fps) {}

		inline void SetAnimationFPS(float _fps) { m_AnimationFPS = _fps; }

		inline void AddAnimationTexture(std::string _TexturePath) {
			CORE_INFO("Adding texture {0} to animated sprite", _TexturePath);
			m_AnimationTextures.push_back(Renderer::s_Instance->GetTexture(_TexturePath));
		}

		void Update(float DeltaTime) {
			if (m_AnimationTextures.size() > 0) {
				m_CurrentFrame += m_AnimationFPS * DeltaTime;

				while (m_CurrentFrame >= m_AnimationTextures.size()) {
					m_CurrentFrame -= m_AnimationTextures.size();
				}
			}
		}
	};

	class AnimatedSprite : public Component {
	public:
		AnimatedSprite() { }

		~AnimatedSprite() { }

		void Initialize() override {
			m_CurrentAnimation = nullptr;
		}

		void BeginPlay() override {
			m_SpriteReference = Owner->GetComponentOfType<Sprite>();
		}

		void Update(float DeltaTime) override {
			if (m_CurrentAnimation != nullptr) {
				m_CurrentAnimation->Update(DeltaTime);
				m_SpriteReference->SetTexture(
					m_CurrentAnimation->m_AnimationTextures[static_cast<int>(m_CurrentAnimation->m_CurrentFrame)]
				);
			}
		}

		void Play(std::string AnimationName) {
			if (m_AnimationList.count(AnimationName) != 0) {
				m_CurrentAnimation = m_AnimationList[AnimationName];
			}
		}

		void AddAnimationClip(std::string AnimationName, AnimationClip* Clip) { m_AnimationList.emplace(AnimationName, Clip); }
		AnimationClip* GetAnimationClip(std::string ClipID) {
			if (m_AnimationList.count(ClipID) != 0) {
				return m_AnimationList[ClipID];
			}
		}

		virtual void Destroy() override {
			CORE_INFO("[animated sprite] deleting animation clips on '{0}' entity", Owner->Name);
			for (std::map<std::string, AnimationClip*>::iterator itr = m_AnimationList.begin(); itr != m_AnimationList.end(); itr++) {
				delete itr->second;
			}

			m_SpriteReference = nullptr; // not this component's responsibility to clean the sprite reference
			m_CurrentAnimation = nullptr;
		}

	private:
		Sprite* m_SpriteReference;
		std::map<std::string, AnimationClip*> m_AnimationList;
		AnimationClip* m_CurrentAnimation;
	};
}