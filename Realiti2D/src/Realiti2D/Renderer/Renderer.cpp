#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "SpriteRenderData.h"
#include "Realiti2D/Log.h"
#include <GL/glew.h>

namespace Realiti2D {
	Renderer* Renderer::s_Instance = nullptr;

	// we don't do anything on constructor or destructor because we want to
	// explicitly tell the modules when to do those kind of things
	Renderer::Renderer() {}
	Renderer::~Renderer() {}

	void Renderer::AddToRenderQueue(Texture* Tex, Vector2* Pos, Quaternion* Rot, Vector2* Scale) {
		SpriteRenderData rd = {
			Tex,
			Pos,
			Rot,
			Scale
		};

		m_SpriteRenderDataQueue.push_back(rd);
	}

	bool Renderer::Initialize(float ScreenWidth, float ScreenHeight, std::string WindowTitle) {
		if (s_Instance != nullptr) {
			CORE_ERROR("[renderer] are you trying to initialize the renderer twice?");
			return false;
		}

		s_Instance = this;

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
		
		if (!LoadDefaultShaders()) {
			CORE_ERROR("[renderer] failed to load default shaders");
			return false;
		}
		
		CreateDefaultSpriteVertex();
		
		CORE_INFO("[renderer] renderer initialized");
		return true;

	}

	bool Renderer::LoadDefaultShaders() {
		m_DefaultSpriteShader = new Shader();

		// lol this is awful. help.
		if (!m_DefaultSpriteShader->Load
			(
				"E:\\Workspace\\realiti2D\\Realiti2D\\src\\Realiti2D\\DefaultAssets\\Shaders\\Sprite.vert",
				"E:\\Workspace\\realiti2D\\Realiti2D\\src\\Realiti2D\\DefaultAssets\\Shaders\\Sprite.frag")
			) 
		{
			return false;
		}

		m_DefaultSpriteShader->SetActive();
		return true;
	}

	void Renderer::CreateDefaultSpriteVertex(){
		float vertices[] = {
			-0.5f,  0.5f, 0.0f, 0.0f, 0.0f,		// top left
			0.5f,  0.5f, 0.0f, 1.0f, 0.0f,		// top right
			0.5f, -0.5f, 0.0f, 1.0f, 1.0f,		// bottom right
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,		// bottom left
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_DefaultSpriteVertexArray = new VertexArray(vertices, 4, indices, 6);
	}

	void Renderer::Draw() {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glEnable(GL_BLEND);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

		// TODO: Have an active shader and sprite vertex array pointer?
		m_DefaultSpriteShader->SetActive();
		m_DefaultSpriteVertexArray->SetActive();

		// Camera
		glm::mat4 CameraProjection = glm::ortho(-512.0f, 512.0f, -368.0f, 368.0f, -10.0f, 10.0f);
		glm::mat4 CameraTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
		glm::mat4 CameraView = glm::inverse(CameraTransform);
		glm::mat4 CameraViewProj = CameraProjection * CameraView;
		Matrix4 ViewProj(CameraViewProj);
		m_DefaultSpriteShader->SetMatrixUniform("uViewProj", ViewProj);

		/*
		Texture* tex = GetTexture("E:\\Workspace\\realiti2D\\Realiti2D\\src\\Realiti2D\\DefaultAssets\\Sprites\\kenney_spaceship.png");
		if (tex) {
			glm::mat4 Scale = glm::scale(glm::vec3(106.0f, 80.0f, 1.0f));
			glm::mat4 ActorScale = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
			glm::mat4 ActorTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(100.0f, 0.0f, 0.0f));


			glm::mat4 World = (ActorTranslation * ActorScale) * Scale;
			GLuint loc = glGetUniformLocation(m_DefaultSpriteShader->GetShaderProgram(), "uWorldTransform");
			glUniformMatrix4fv(loc, 1, GL_FALSE, reinterpret_cast<const float*>(&World[0][0]));
			tex->SetActive();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
		*/

		while (!m_SpriteRenderDataQueue.empty()) {
			SpriteRenderData RenderData = m_SpriteRenderDataQueue[0];
			m_SpriteRenderDataQueue.erase(m_SpriteRenderDataQueue.begin());

			if (RenderData.Texture) {

				Matrix4 ScaleMat = Matrix4::CreateScale(
					static_cast<float>(RenderData.Texture->GetWidth()),
					static_cast<float>(RenderData.Texture->GetHeight()),
					1.0f
				);

				Matrix4 WorldScale = Matrix4::CreateScale(RenderData.Scale->x, RenderData.Scale->y, 1.0f);
				Matrix4 WorldRotation = Matrix4::CreateFromQuaternion(*RenderData.Rotation);
				glm::mat4 rotated = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, -1.0f));
				Matrix4 WorldRotation2(rotated);
				Matrix4 WorldTranslation = Matrix4::CreateTranslation(RenderData.Position->x, RenderData.Position->y, 0.0f);

				Matrix4 World = (WorldTranslation * WorldRotation2 * WorldScale) * ScaleMat;
				m_DefaultSpriteShader->SetMatrixUniform("uWorldTransform", World);

				RenderData.Texture->SetActive();
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			}
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