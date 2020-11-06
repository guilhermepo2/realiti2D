#pragma once
#include <SDL.h>
#include <string>
#include <unordered_map>

namespace Realiti2D {

	class Texture;
	class Shader;
	class VertexArray;

	class Renderer {
	public:
		Renderer();
		~Renderer();

		bool Initialize(float ScreenWidth, float ScreenHeight, std::string WindowTitle);
		void Draw();
		void Shutdown();

		void LoadTexture(const std::string& filePath);
		Texture* GetTexture(const std::string& fileName);

		inline float GetScreenWidth() const { return m_ScreenWidth; }
		inline float GetScreenHeight() const { return m_ScreenHeight; }
		inline std::string GetWindowTitle() const { return m_WindowTitle; }
		inline SDL_Window* GetWindow() { return m_Window; }
		inline SDL_GLContext& GetContext() { return m_GLContext; }
	private:
		bool LoadDefaultShaders();
		void CreateDefaultSpriteVertex();

		float m_ScreenWidth;
		float m_ScreenHeight;
		std::string m_WindowTitle;

		// Loaded Textures
		std::unordered_map<std::string, Texture*> m_Textures;
		Shader* m_DefaultSpriteShader;
		VertexArray* m_DefaultSpriteVertexArray;

		SDL_Window* m_Window;
		SDL_GLContext m_GLContext;
	};
}