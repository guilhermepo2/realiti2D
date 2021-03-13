#pragma once
#include "Layer.h"

namespace Realiti2D {
	
	class Application;
	class ImGuiWindowLayer;
	class ImGuiWindow;

	class ImGuiWindow {
	public:
		ImGuiWindow(Application* app, const std::string& WindowName);
		virtual void DrawWindow() {}

	private:
		ImGuiWindowLayer* m_LayerRef = nullptr;
	};

	class ImGuiWindowLayer : Layer {
	public:
		ImGuiWindowLayer(Application* app, const std::string& Name, ImGuiWindow* window);
		void Render();

	private:
		ImGuiWindow* m_Window;
	};
}