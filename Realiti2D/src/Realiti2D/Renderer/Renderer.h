#pragma once
#include <SDL.h>
#include <string>

namespace Realiti2D {
	class Renderer {
	public:
		Renderer();
		~Renderer();

		bool Initialize(float ScreenWidth, float ScreenHeight, std::string WindowTitle);
		void Draw();
		void Shutdown();

		inline float GetScreenWidth() const { return m_ScreenWidth; }
		inline float GetScreenHeight() const { return m_ScreenHeight; }
		inline std::string GetWindowTitle() const { return m_WindowTitle; }
		inline SDL_Window* GetWindow() { return m_Window; }
		inline SDL_GLContext& GetContext() { return m_GLContext; }
	private:
		float m_ScreenWidth;
		float m_ScreenHeight;
		std::string m_WindowTitle;

		SDL_Window* m_Window;
		SDL_GLContext m_GLContext;
	};
}