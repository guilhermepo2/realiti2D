#include "GameLayer.h"
#include "Realiti2D/Collision/CollisionWorld.h"
#include "Realiti2D/UI/UIScreen.h"

namespace Realiti2D {
	void GameLayer::Initialize() {
		CORE_INFO("[GAME LAYER] Initializing Game Layer");
		
		m_EntityManager = new EntityManager();
		
		m_CollisionWorld = new CollisionWorld();
		ASSERT(m_CollisionWorld->Initialize(), "[application] unable to initialize collision world");
		
		m_bShowDebugColliders = false;

		for (auto& ui : m_UIScreenStack) {
			ui->Initialize();
		}
	}

	void GameLayer::Destroy() {
		m_EntityManager->Destroy();
		delete m_EntityManager;

		m_CollisionWorld->Shutdown();
		delete m_CollisionWorld;

		for (auto& ui : m_UIScreenStack) {
			ui->Destroy();
			delete ui;
		}
	}

	void GameLayer::BeginPlay() {
		m_EntityManager->BeginPlay();

		for (auto& ui : m_UIScreenStack) {
			ui->BeginPlay();
		}
	}

	void GameLayer::Update(float DeltaTime) {
		m_EntityManager->Update(DeltaTime);
		m_CollisionWorld->VerifyAllCollisions();

		for (auto& ui : m_UIScreenStack) {
			ui->Update(DeltaTime);
		}
	}

	bool GameLayer::OnSDLEvent(SDL_Event& Event) {
		return false;
	}

	bool GameLayer::OnApplicationEvent(const InputState& CurrentInputState) {
		if (CurrentInputState.Keyboard.WasKeyPressedThisFrame(KEYCODE_F1)) {
			m_bShowDebugColliders = !m_bShowDebugColliders;
			return true;
		}

		return m_EntityManager->ProcessInput(CurrentInputState);

		for (auto& ui : m_UIScreenStack) {
			if (ui->ProcessInput(CurrentInputState)) {
				break; // if a UI handle an input, we don't want to propagate that
			}
		}
	}

	void GameLayer::Render() {
		m_EntityManager->Render();

		if (m_bShowDebugColliders) {
			m_CollisionWorld->Render();
		}

		for (auto& ui : m_UIScreenStack) {
			ui->Render();
		}
	}

}