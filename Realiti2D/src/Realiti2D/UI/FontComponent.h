#pragma once
#include "Font.h"
#include "Realiti2D/Component/Component.h"
#include "Realiti2D/Component/TransformComponent.h"
#include "Realiti2D/Entity/Entity.h"
#include "Realiti2D/Renderer/Renderer.h"
#include "Realiti2D/Renderer/Texture.h"

namespace Realiti2D {
	class FontComponent : public Component {
	public:
		FontComponent(const std::string& FontName) {
			m_Font = new Font();
			m_Font->Load(FontName);
			m_FontTexture = nullptr;
		}

		void Destroy() override {
			if (m_Font != nullptr) {
				m_Font->Unload();
				delete m_Font;
			}
		}

		void Render() override {
			Transform* ownerTransform = Owner->GetComponentOfType<Transform>();

			if (ownerTransform != nullptr && m_FontTexture != nullptr) {
				Renderer::s_Instance->AddToRenderQueue(m_FontTexture, &(ownerTransform->Position), 0.0f, &(ownerTransform->Scale), 100);
			}
		}

		void UpdateText(const std::string& Text) {
			if (m_FontTexture != nullptr) {
				m_FontTexture->Unload();
				delete m_FontTexture;
			}

			m_FontTexture = m_Font->RenderTexture(Text);
		}

	private:
		Font* m_Font;
		Texture* m_FontTexture;
	};
}
