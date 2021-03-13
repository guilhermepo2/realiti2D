#include "ImGuiWindow.h"
#include "Realiti2D/Application.h"

namespace Realiti2D {
	// =============================================================
	// =============================================================
	// 	   IMGUI WINDOW
	// =============================================================
	// =============================================================
	ImGuiWindow::ImGuiWindow(Application* app, const std::string& WindowName) {
		m_LayerRef = new ImGuiWindowLayer(app, WindowName, this);
	}

	// =============================================================
	// =============================================================
	// 	   IMGUI WINDOW LAYER
	// =============================================================
	// =============================================================
	ImGuiWindowLayer::ImGuiWindowLayer(Application* app, const std::string& Name, ImGuiWindow* window) : Layer(Name) {
		m_Window = window;
		app->PushLayer(this);
	}

	void ImGuiWindowLayer::Render() {
		m_Window->DrawWindow();
	}
}