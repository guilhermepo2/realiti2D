#pragma once
#include "Component.h"
#include "Realiti2D/Log.h"
#include "Realiti2D/Renderer/Renderer.h"

namespace Realiti2D {
	
	class Texture;

	class Sprite : public Component {
	public:
		Texture* tex;
		int DrawOrder;

		Sprite() : tex(nullptr) {}
		
		Sprite(const std::string& TexturePath, int _DrawOrder) {
			tex = Renderer::s_Instance->GetTexture(TexturePath);
			DrawOrder = _DrawOrder;
		}

		void SetTexture(Texture* _tex) {
			if (_tex != nullptr) {
				tex = _tex;
			}
		}
	};
}