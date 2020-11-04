#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
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

		//
		// TEMP - HAVE A SPECIAL FUNCTIONS FOR THESE THIGNS!!
		//
		// loading shaders
		m_DefaultSpriteShader = new Shader();
		
		// lol this is awful. help.
		if (!m_DefaultSpriteShader->Load(
			"E:\\Workspace\\realiti2D\\Realiti2D\\src\\Realiti2D\\DefaultAssets\\Shaders\\Sprite.vert", 
			"E:\\Workspace\\realiti2D\\Realiti2D\\src\\Realiti2D\\DefaultAssets\\Shaders\\Sprite.frag")) {
			return false;
		}

		m_DefaultSpriteShader->SetActive();
		Matrix4 ViewProj = Matrix4::CreateSimpleViewProj(m_ScreenWidth, m_ScreenHeight);
		m_DefaultSpriteShader->SetMatrixUniform("uViewProj", ViewProj);
		// End of loading shaders

		// Creating sprite vertices....
		float vertices[] = {
			-0.5f,  0.5f, 0.0f, 0.0f, 0.0f,		// top left
			0.5f,  0.5f, 0.0f, 1.0f, 0.0f,		// top right
			0.5f, -0.5f, 0.0f, 1.0f, 1.0f,		// bottom right
		-	0.5f, -0.5f, 0.0f, 0.0f, 1.0f,		// bottom left
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_DefaultSpriteVertexArray = new VertexArray(vertices, 4, indices, 6);

		CORE_INFO("[renderer] renderer initialized");
		return true;

	}

	void Renderer::Draw() {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glEnable(GL_BLEND);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

		// Have an active shader and sprite vertex array pointer?
		m_DefaultSpriteShader->SetActive();
		m_DefaultSpriteVertexArray->SetActive();
		// Draw Something... ?

		Texture* myTexture = GetTexture("E:\\Workspace\\realiti2D\\Realiti2D\\src\\Realiti2D\\DefaultAssets\\Sprites\\kenney_spaceship.png");
		if (myTexture) {
			// Creating scale matrix
			Matrix4 ScaleMat = Matrix4::CreateScale(
				static_cast<float>(myTexture->GetWidth()),
				static_cast<float>(myTexture->GetHeight()),
				1.0f
			);

			// Calculating World Transform...
			Matrix4 WorldTransform = Matrix4::CreateScale(1.0f, 1.0f, 1.0f);
			WorldTransform *= Matrix4::CreateFromQuaternion(Quaternion::Identity);
			WorldTransform *= Matrix4::CreateTranslation(0.0f, 0.0f, 0.0f);
			Matrix4 World = ScaleMat * WorldTransform;
			m_DefaultSpriteShader->SetMatrixUniform("uWorldTransform", World);

			myTexture->SetActive();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}

		SDL_GL_SwapWindow(m_Window);
	}

	void Renderer::Shutdown() {
		CORE_INFO("[renderer] shutting down renderer");
		SDL_GL_DeleteContext(m_GLContext);
		SDL_DestroyWindow(m_Window);
	}

	// ---------------------------------------------------------------
	// Draw
	// ---------------------------------------------------------------

	Texture* Renderer::GetTexture(const std::string& fileName) {
		Texture* tex = nullptr;
		auto iter = m_Textures.find(fileName);

		if (iter != m_Textures.end()) {
			tex = iter->second;
		}
		else {

			tex = new Texture();
			if (tex->Load(fileName)) {
				m_Textures.emplace(fileName, tex);
			}
			else {
				CORE_WARNING("[renderer] could not find texture: {0}", fileName);
				delete tex;
				tex = nullptr;
			}

		}

		return tex;
	}
}