#pragma once
#include "Component.h"
#include "Realiti2D/Log.h"
#include "Realiti2D/Renderer/Renderer.h"

namespace Realiti2D {
	
	class Texture;

	class Sprite : public Component {
	public:
		Texture* tex;

		Sprite() : tex(nullptr) {}
		
		Sprite(const std::string& TexturePath) {
			tex = Renderer::s_Instance->GetTexture(TexturePath);
		}

		void SetTexture(Texture* _tex) {
			if (_tex != nullptr) {
				tex = _tex;
			}
		}
	};
}