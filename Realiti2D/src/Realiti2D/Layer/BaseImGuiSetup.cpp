#include "BaseImGuiSetup.h"

#include "Realiti2D/Renderer/Renderer.h"
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <GL/glew.h>

namespace Realiti2D {
	void BaseImGuiLayer::Initialize() {
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
			Renderer::s_Instance->GetWindow(),
			Renderer::s_Instance->GetContext()
		);
		ImGui_ImplOpenGL3_Init("#version 330");
		// TODO: Load Fonts (?)
	}

	void BaseImGuiLayer::Destroy() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	bool BaseImGuiLayer::OnSDLEvent(SDL_Event* Event) {
		return ImGui_ImplSDL2_ProcessEvent(Event);
	}

	void BaseImGuiLayer::PrepareToRender() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(Realiti2D::Renderer::s_Instance->GetWindow());
		ImGui::NewFrame();
	}

	void BaseImGuiLayer::PostRender() {
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
}