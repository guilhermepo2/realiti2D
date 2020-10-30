#include "Application.h"
#include "Log.h"
#include "Renderer/Renderer.h"

const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;

namespace Realiti2D {
	
	bool Application::s_bIsInitialized = false;

	Application::Application(const float& Width, const float& Height, const std::string& Title)
		: m_Renderer(nullptr),
		m_bIsRunning(false),
		m_TicksLastFrame(0.0f) {
		CORE_INFO("[APPLICATION] Initializing Application");
		m_Renderer = new Renderer();
		
		bool Result = m_Renderer->Initialize(Width, Height, Title);

		if (!Result) {
			CORE_ERROR("[ENTRY POINT] Unable to initialize Renderer!");
			return;
		}

		s_bIsInitialized = true;
		m_bIsRunning = true;
	}

	Application::~Application() {
		CORE_INFO("[APPLICATION] Shutting down application");
		m_Renderer->Shutdown();
		delete m_Renderer;
	}

	void Application::Run() {
		CORE_INFO("[APPLICATION] Running app");
		// Start?

		while (m_bIsRunning) {
			// -------------------------------------------
			float DeltaTime = (SDL_GetTicks() - m_TicksLastFrame) / 1000.0f;
			DeltaTime = (DeltaTime > 0.05f) ? 0.05f : DeltaTime;
			m_TicksLastFrame = SDL_GetTicks();

			// -------------------------------------------
			ProcessInput();
			Update(DeltaTime);
			Render();

			// -------------------------------------------
			int TimeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - m_TicksLastFrame);
			if (TimeToWait > 0.0f && TimeToWait <= FRAME_TARGET_TIME) {
				SDL_Delay(TimeToWait);
			}
		}
	}

	void Application::Start() { }

	void Application::ProcessInput() {
		SDL_Event FrameEvent;
		while (SDL_PollEvent(&FrameEvent)) {
			switch (FrameEvent.type) {
			case SDL_QUIT:
				m_bIsRunning = false;
				break;
			default:
				break;
			}
		}
	}

	void Application::Update(float DeltaTime) {
		return;
	}

	void Application::Render() {
		m_Renderer->Draw();
		return;
	}
}