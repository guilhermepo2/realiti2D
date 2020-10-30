#pragma once
#include <SDL.h>

class Renderer {
public:
	Renderer();
	~Renderer();

	bool Initialize(float ScreenWidth, float ScreenHeight);
	void Shutdown();

	inline float GetScreenWidth() const		{ return m_ScreenWidth;		}
	inline float GetScreenHeight() const	{ return m_ScreenHeight;	}
	inline SDL_Window* GetWindow()			{ return m_Window;			}
	inline SDL_GLContext& GetContext()		{ return m_GLContext;		}
private:
	float m_ScreenWidth;
	float m_ScreenHeight;

	SDL_Window* m_Window;
	SDL_GLContext m_GLContext;
};