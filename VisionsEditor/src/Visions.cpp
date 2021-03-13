#include <Realiti2D.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define VISIONS_EDITOR
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <GL/glew.h>

class VisionsLayer : public Realiti2D::Layer {
public:
	VisionsLayer() : Realiti2D::Layer("Visions") {}

	void Initialize() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;	// enable keyboard control
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		// enable docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;		// enable multi-viewport
		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// setting up platform renderer backend
		ImGui_ImplSDL2_InitForOpenGL(
			Realiti2D::Renderer::s_Instance->GetWindow(),
			Realiti2D::Renderer::s_Instance->GetContext()
		);
		ImGui_ImplOpenGL3_Init("#version 330");
		// TODO: Load Fonts (?)
	}

	void Destroy() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	bool OnSDLEvent(SDL_Event* Event) {
		return ImGui_ImplSDL2_ProcessEvent(Event);
	}

	void PrepareToRender() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(Realiti2D::Renderer::s_Instance->GetWindow());
		ImGui::NewFrame();
	}

	virtual void Render() {
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

		ImGui::ShowDemoWindow();
	}

	virtual void PostRender() {
		ImGui::Render();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			SDL_Window* BackupCurrentWindow = SDL_GL_GetCurrentWindow();
			SDL_GLContext BackupCurrentContext = SDL_GL_GetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			SDL_GL_MakeCurrent(BackupCurrentWindow, BackupCurrentContext);
		}
	}
};

class Visions : public Realiti2D::Application {
public:
	Visions(const float& Width, const float& Height, const std::string& Title) : Application(Width, Height, Title) {}
	~Visions() {}

	void Start() override {
		DEBUG_INFO("Starting Visions Editor]");
		VisionsLayer* l = new VisionsLayer();
		PushLayer(l);
	}

private:

};

Realiti2D::Application* Realiti2D::CreateApplication() {
	return new Visions(SCREEN_WIDTH, SCREEN_HEIGHT, "Visions Editor");
}