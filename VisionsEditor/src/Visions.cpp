#include <Realiti2D.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define VISIONS_EDITOR
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <GL/glew.h>

class VisionsWindow : public Realiti2D::ImGuiWindow {
public:
	VisionsWindow(Realiti2D::Application* app, const std::string& WindowName) : ImGuiWindow(app, WindowName) {}

	void DrawWindow() {
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

		if (ImGui::BeginMainMenuBar()) {

			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Options")) {
				if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		ImGui::Begin("Entities");
		for (int i = 0; i < m_Entities.size(); i++) {
			ImGui::LabelText("Name", "Entity");
		}

		if (ImGui::SmallButton("Add Entity")) {
			m_Entities.push_back("Entity");
		}

		if (ImGui::SmallButton("Save JSON")) {
			//
		}

		ImGui::End();
	}

private:
	std::vector<std::string> m_Entities;
};

class Visions : public Realiti2D::Application {
public:
	Visions(const float& Width, const float& Height, const std::string& Title) : Application(Width, Height, Title) {}
	~Visions() {}

	void Start() override {
		DEBUG_INFO("Starting Visions Editor]");
		Realiti2D::BaseImGuiLayer* l = new Realiti2D::BaseImGuiLayer();
		PushLayer(l);

		VisionsWindow* w = new VisionsWindow(this, "Visions Editor");
	}

private:

};

Realiti2D::Application* Realiti2D::CreateApplication() {
	return new Visions(SCREEN_WIDTH, SCREEN_HEIGHT, "Visions Editor");
}