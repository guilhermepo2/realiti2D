#include "Renderer.h"
#include "Realiti2D/Log.h"
#include <GL/glew.h>

// we don't do anything on constructor or destructor because we want to
// explicitly tell the modules when to do those kind of things
Renderer::Renderer() {}
Renderer::~Renderer() {}

bool Renderer::Initialize(float ScreenWidth, float ScreenHeight) {
	m_ScreenWidth = ScreenWidth;
	m_ScreenHeight = ScreenHeight;

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
		"Realiti2D",		// TODO: Make the Window Title customizable (or just have it to be the editor's name in case that's what we're going for)
		100, 100,			// top left and y coordinates of the window... whatever
		static_cast<int>(m_ScreenWidth), static_cast<int>(m_ScreenHeight),
		SDL_WINDOW_OPENGL
	);

	if (!m_Window) {
		CORE_ERROR("Unable to create window: %s", SDL_GetError());
		return false;
	}

	// Creating the OpenGL Context
	m_GLContext = SDL_GL_CreateContext(m_Window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		CORE_ERROR("Unable to initialize GLEW.");
		return false;
	}
	glGetError(); // on some platformrs GLEW will emit a benign error code, clean it.

	return true;

}

void Renderer::Shutdown() {
	SDL_GL_DeleteContext(m_GLContext);
	SDL_DestroyWindow(m_Window);
}