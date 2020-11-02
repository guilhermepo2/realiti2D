#include "Renderer.h"
#include "Realiti2D/Log.h"
#include <GL/glew.h>

namespace Realiti2D {
	// we don't do anything on constructor or destructor because we want to
	// explicitly tell the modules when to do those kind of things
	Renderer::Renderer() {}
	Renderer::~Renderer() {}

	bool Renderer::Initialize(float ScreenWidth, float ScreenHeight, std::string WindowTitle) {
		m_ScreenWidth = ScreenWidth;
		m_ScreenHeight = ScreenHeight;
		m_WindowTitle = WindowTitle;

		// Setting a bunch of OpenGL stuff
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);	// OpenGL core
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);							// Version 3.3
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);										// Color sizes, 8 bits for RGBA = 32 bits = 4 bytes = good enough
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);										// I don't think I need this?
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);									// Enables double buffering
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		m_Window = SDL_CreateWindow(
			m_WindowTitle.c_str(),
			100, 100,				// top left and y coordinates of the window... whatever
			static_cast<int>(m_ScreenWidth), static_cast<int>(m_ScreenHeight),
			SDL_WINDOW_OPENGL
		);

		if (!m_Window) {
			CORE_ERROR("[renderer] unable to create window: %s", SDL_GetError());
			return false;
		}

		// Creating the OpenGL Context
		m_GLContext = SDL_GL_CreateContext(m_Window);
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			CORE_ERROR("[renderer] unable to initialize glew.");
			return false;
		}
		glGetError(); // on some platformrs GLEW will emit a benign error code, clean it.

		CORE_INFO("[renderer] renderer initialized");
		return true;

	}

	void Renderer::Draw() {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(m_Window);
	}

	void Renderer::Shutdown() {
		CORE_INFO("[renderer] shutting down renderer");
		SDL_GL_DeleteContext(m_GLContext);
		SDL_DestroyWindow(m_Window);
	}
}