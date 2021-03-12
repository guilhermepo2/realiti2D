#pragma once
#include <string>
#include <SDL.h>
#include "Realiti2D/Input/Input.h"

namespace Realiti2D {
	class Layer {
	public:
		Layer(const std::string& Name = "Layer");
		virtual ~Layer() {}

		virtual void Initialize() {}
		virtual void Destroy() {}

		virtual void BeginPlay() {}
		virtual void Update(float DeltaTime) {}
		virtual void ImGuiRender() {}
		virtual bool OnSDLEvent(SDL_Event& Event) { return false; }
		virtual bool OnApplicationEvent(const InputState& CurrentInputState) { return false; }
		virtual void Render() {}

	private:
		std::string m_LayerName;
	};
}