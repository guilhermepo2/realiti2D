#pragma once
#include "Layer.h"

namespace Realiti2D {
	class BaseImGuiLayer : public Layer {
	public:
		BaseImGuiLayer() : Layer("BaseImGui") {}

		void Initialize();
		void Destroy();

		bool OnSDLEvent(SDL_Event* Event);
		void PrepareToRender();
		void PostRender();
	};
}
