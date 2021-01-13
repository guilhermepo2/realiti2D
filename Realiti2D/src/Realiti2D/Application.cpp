#include "Application.h"
#include "Log.h"
#include "Input/Input.h"
#include "Renderer/Renderer.h"
#include "Entity/EntityManager.h"
#include "Collision/CollisionWorld.h"


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

		m_EntityManager = new EntityManager();

		m_CollisionWorld = new CollisionWorld();
		ASSERT(m_CollisionWorld->Initialize(), "[application] unable to initialize collision world");

		s_bIsInitialized = true;
		m_bIsRunning = true;
	}

	Application::~Application() {
		CORE_INFO("[application] shutting down application");

		m_Renderer->Shutdown();
		delete m_Renderer;

		m_InputSystem->Shutdown();
		delete m_InputSystem;

		m_EntityManager->Destroy(); // is Destroy() here the right function to call?
		delete m_EntityManager;


	}

	void Application::Run() {
		CORE_INFO("[application] running app");

		Start();
		m_EntityManager->BeginPlay();

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
		m_InputSystem->PrepareForUpdate();

		SDL_Event FrameEvent;
		while (SDL_PollEvent(&FrameEvent)) {
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

		// TODO: Update all actors?
		// I'm still not sure if I will have a dedicated input function for actors, maybe just do this on the update?
		m_EntityManager->ProcessInput(m_InputSystem->GetState());
	}

	void Application::Update(float DeltaTime) {
		m_EntityManager->Update(DeltaTime);
		return;
	}

	void Application::Render() {

		m_EntityManager->Render();
		m_Renderer->Draw();
		return;
	}
}
