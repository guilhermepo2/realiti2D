#pragma once
#include "Entity/EntityManager.h"

namespace Realiti2D {

	class CollisionWorld;
	class EntityManager;
	class GameLayer;
	class InputSystem;
	class Layer;
	class LayerStack;
	class Renderer;

	class Application {
	public:
		Application(const float& Width, const float& Height, const std::string& Title);
		~Application();

		void Run();

		static bool s_bIsInitialized;
		void PushLayer(Layer* _Layer);

	protected:
		virtual void Start();
		void ProcessInput();
		void Update(float DeltaTime);

		void PrepareToRender();
		void Render();
		void PostRender();

		GameLayer* PushGameLayer();

	private:
		bool m_bIsRunning;
		float m_TicksLastFrame;

		Renderer* m_Renderer;
		InputSystem* m_InputSystem;
		LayerStack* m_LayerStack;
	};

	// Defined in the client...
	Application* CreateApplication();
}