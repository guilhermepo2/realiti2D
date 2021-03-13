#include "GameLayer.h"
#include "Realiti2D/Collision/CollisionWorld.h"

namespace Realiti2D {
	void GameLayer::Initialize() {
		CORE_INFO("[GAME LAYER] Initializing Game Layer");
		m_EntityManager = new EntityManager();
		m_CollisionWorld = new CollisionWorld();
		ASSERT(m_CollisionWorld->Initialize(), "[application] unable to initialize collision world");
		m_bShowDebugColliders = false;
	}

	void GameLayer::Destroy() {
		m_EntityManager->Destroy();
		delete m_EntityManager;

		m_CollisionWorld->Shutdown();
		delete m_CollisionWorld;
	}

	void GameLayer::BeginPlay() {
		m_EntityManager->BeginPlay();
	}

	void GameLayer::Update(float DeltaTime) {
		m_EntityManager->Update(DeltaTime);
		m_CollisionWorld->VerifyAllCollisions();
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
	}

	void GameLayer::Render() {
		m_EntityManager->Render();

		if (m_bShowDebugColliders) {
			m_CollisionWorld->Render();
		}
	}
}