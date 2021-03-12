#pragma once
#include <string>
#include <SDL.h>
#include "Realiti2D/Input/Input.h"

namespace Realiti2D {
	class Layer {
	public:
		Layer(const std::string& Name = "Layer");
		virtual ~Layer();

		virtual void Initialize() {}
		virtual void Destroy() {}

		virtual void Update(float DeltaTime) {}
		virtual void ImGuiRender() {}
		virtual void OnSDLEvent(SDL_Event& Event) {}
		virtual void OnApplicationEvent(const InputState& CurrentInputState) {}

	private:
		std::string m_LayerName;
	};
}