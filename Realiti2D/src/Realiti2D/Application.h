#pragma once
#include <string>

namespace Realiti2D {

	class Renderer;

	class Application {
	public:
		Application(const float& Width, const float& Height, const std::string& Title);
		~Application();

		void Run();

		static bool s_bIsInitialized;

	protected:
		virtual void Start();
		void ProcessInput();
		void Update(float DeltaTime);
		void Render();

	private:
		bool m_bIsRunning;
		float m_TicksLastFrame;
		Renderer* m_Renderer;
	};

	// Defined in the client...
	Application* CreateApplication();
}