#include "Application.h"
#include "Log.h"
#include "Input/Input.h"
#include "Renderer/Renderer.h"
#include "Entity/EntityManager.h"
#include "Collision/CollisionWorld.h"
#include "Layer/LayerStack.h"
#include "Layer/GameLayer.h"

const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;

namespace Realiti2D {
	
	bool Application::s_bIsInitialized = false;

	Application::Application(const float& Width, const float& Height, const std::string& Title)
		: m_Renderer(nullptr),
		m_InputSystem(nullptr),
		m_bIsRunning(false),
		m_TicksLastFrame(0.0f) {

		CORE_INFO("[application] initializing application");
		ASSERT(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER), "[application] unable to initialize sdl");

		m_Renderer = new Renderer();
		ASSERT(m_Renderer->Initialize(Width, Height, Title), "[application] unable to initialize renderer");

		m_InputSystem = new InputSystem();
		ASSERT(m_InputSystem->Initialize(), "[application] unable to initialize input system");

		m_LayerStack = new LayerStack();

		s_bIsInitialized = true;
		m_bIsRunning = true;
	}

	void Application::PushLayer(Layer* _Layer) {
		_Layer->Initialize();
		m_LayerStack->PushLayer(_Layer);
	}

	GameLayer* Application::PushGameLayer() {
		GameLayer* gl = new GameLayer();
		gl->Initialize();
		m_LayerStack->PushLayer(gl);
		return gl;
	}

	Application::~Application() {
		CORE_INFO("[application] shutting down application");

		m_Renderer->Shutdown();
		delete m_Renderer;

		m_InputSystem->Shutdown();
		delete m_InputSystem;

		delete m_LayerStack;

	}

	void Application::Run() {
		CORE_INFO("[application] running app");

		Start();
		// begin play is a game specific concept... duh...
		for (Layer* l : m_LayerStack->GetLayers()) {
			l->BeginPlay();
		}

		while (m_bIsRunning) {
			// -------------------------------------------
			float DeltaTime = (SDL_GetTicks() - m_TicksLastFrame) / 1000.0f;
			DeltaTime = (DeltaTime > 0.05f) ? 0.05f : DeltaTime;
			m_TicksLastFrame = SDL_GetTicks();

			// -------------------------------------------
			ProcessInput();
			Update(DeltaTime);

			PrepareToRender();
			Render();
			PostRender();

			// -------------------------------------------
			int TimeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - m_TicksLastFrame);
			if (TimeToWait > 0.0f && TimeToWait <= FRAME_TARGET_TIME) {
				SDL_Delay(TimeToWait);
			}
		}
	}

	void Application::Start() { }

	void Application::ProcessInput() {
		m_InputSystem->PrepareForUpdate();

		SDL_Event FrameEvent;
		while (SDL_PollEvent(&FrameEvent)) {

			for (Layer* l : m_LayerStack->GetLayers()) {
				l->OnSDLEvent(&FrameEvent);
			}

			switch (FrameEvent.type) {
			case SDL_QUIT:
				m_bIsRunning = false;
				break;
			default:
				m_InputSystem->ProcessEvent(FrameEvent);
				break;
			}
		}

		m_InputSystem->Update();

		if (m_InputSystem->GetState().Keyboard.WasKeyPressedThisFrame(KEYCODE_ESCAPE)) {
			m_bIsRunning = false;
		}
		else if (m_InputSystem->GetState().Keyboard.WasKeyPressedThisFrame(KEYCODE_F2)) {
			m_Renderer->ToggleRenderImGui();
		}

		for (Layer* l : m_LayerStack->GetLayers()) {
			if (l->OnApplicationEvent(m_InputSystem->GetState())) {
				break;
			}
		}
	}

	void Application::Update(float DeltaTime) {

		for (Layer* l : m_LayerStack->GetLayers()) {
			l->Update(DeltaTime);
		}

	}

	void Application::PrepareToRender() {
		m_Renderer->PrepareToRender();

		for (Layer* l : m_LayerStack->GetLayers()) {
			l->PrepareToRender();
		}
	}

	void Application::Render() {

		m_Renderer->Draw();

		for (Layer* l : m_LayerStack->GetLayers()) {
			l->Render();
		}


		return;
	}

	void Application::PostRender() {
		for (Layer* l : m_LayerStack->GetLayers()) {
			l->PostRender();
		}

		m_Renderer->SwapWindow();
	}
}
