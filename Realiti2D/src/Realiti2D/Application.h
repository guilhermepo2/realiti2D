#pragma once
#include "Entity/EntityManager.h"

namespace Realiti2D {

	class EntityManager;
	class Renderer;
	class InputSystem;
	class CollisionWorld;

	class Application {
	public:
		Application(const float& Width, const float& Height, const std::string& Title);
		~Application();

		void Run();

		static bool s_bIsInitialized;

		Entity& AddEntity(std::string InName) { return m_EntityManager->AddEntity(InName); };
		Entity* GetEntityByName(std::string InName) { return m_EntityManager->GetEntityByName(InName); }

	protected:
		virtual void Start();
		void ProcessInput();
		void Update(float DeltaTime);
		void Render();

	private:
		bool m_bIsRunning;
		float m_TicksLastFrame;

		EntityManager* m_EntityManager;
		Renderer* m_Renderer;
		InputSystem* m_InputSystem;
		CollisionWorld* m_CollisionWorld;
		bool m_bShowDebugColliders;
	};

	// Defined in the client...
	Application* CreateApplication();
}