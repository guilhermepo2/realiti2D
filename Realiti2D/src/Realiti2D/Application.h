#pragma once
#include <string>

#include "Realiti2D/Entity/Entity.h"
#include "Realiti2D/Entity/EntityManager.h"

namespace Realiti2D {

	class EntityManager;
	class Renderer;
	class InputSystem;

	class Application {
	public:
		Application(const float& Width, const float& Height, const std::string& Title);
		~Application();

		void Run();

		static bool s_bIsInitialized;

		Entity& AddEntity(std::string InName) { return m_EntityManager->AddEntity(InName); };

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
	};

	// Defined in the client...
	Application* CreateApplication();
}