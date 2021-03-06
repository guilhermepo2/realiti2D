#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "SpriteRenderData.h"
#include "Realiti2D/Log.h"
#include <GL/glew.h>
#include "Color.h"

#define DEFAULT_ASSETS_PATH std::string("C:\\workspace\\jumpv.main\\realiti2D\\Realiti2D\\src\\Realiti2D\\DefaultAssets\\")
#define DEFAULT_ASSET(x) DEFAULT_ASSETS_PATH+x

namespace Realiti2D {
	Renderer* Renderer::s_Instance = nullptr;

	// we don't do anything on constructor or destructor because we want to
	// explicitly tell the modules when to do those kind of things
	Renderer::Renderer() {}
	Renderer::~Renderer() {}
  
	void Renderer::AddToRenderQueue(Texture* Tex, Vector2* Pos, float Rot, Vector2* Scale, int DrawOrder, Color* _Color) {
		SpriteRenderData rd = {
			Tex,
			Pos,
			Rot,
			Scale,
			DrawOrder,
			_Color,
      
			Tex->GetWidth(),
			Tex->GetHeight()
		};

		// Ordered Sort here...
		std::vector<SpriteRenderData>::iterator iter = m_SpriteRenderDataQueue.begin();
		for (; iter != m_SpriteRenderDataQueue.end(); ++iter) {
			if ( rd.DrawOrder < (*iter).DrawOrder) {
				break;
			}
		}

		m_SpriteRenderDataQueue.insert(iter, rd);
	}

	void Renderer::AddToRenderQueue(Texture* Tex, Vector2* Pos, float Rot, Vector2* Scale, int DrawOrder) {
		AddToRenderQueue(Tex, Pos, Rot, Scale, DrawOrder, m_White);
	}

	void Renderer::AddQuadToRenderQueue(Vector2* Pos, int Width, int Height, Vector2* Scale) {
		Texture* tex = GetTexture(DEFAULT_ASSET("White.png"));
		tex->SetWidth(Width);
		tex->SetHeight(Height);

		AddToRenderQueue(
			tex,
			Pos,
			0,
			Scale,
			100,
			m_CollisionDebugRed
		);
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
		CORE_INFO("[renderer] initializing default textures...");
		// [FIX] THIS IS TERRIBLE
		Texture* white = GetTexture(DEFAULT_ASSET("White.png"));
		
		if (white != nullptr) { CORE_INFO("[renderer] Loaded white texture"); } 
		else { CORE_WARNING("[renderer] failed to load white texture!"); }

		m_White = new Color(1.0f, 1.0f, 1.0f, 1.0f);
		m_CollisionDebugRed = new Color(1.0f, 0.0f, 0.0f, 0.5f);
		m_OrtographicCamera = new OrtographicCamera(m_ScreenWidth, m_ScreenHeight);
		m_OrtographicCamera->SetBackgroundColor(0.5f, 0.5f, 0.5f, 1.0f);
		
		return true;
	}

	bool Renderer::LoadDefaultShaders() {
		m_DefaultSpriteShader = new Shader();

		// [FIX] THIS IS TERRIBLE
		if (!m_DefaultSpriteShader->Load
			(
				DEFAULT_ASSET("Shaders\\Sprite.vert"),
				DEFAULT_ASSET("Shaders\\Sprite.frag"))
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
		glClearColor(
			m_OrtographicCamera->R(),
			m_OrtographicCamera->G(),
			m_OrtographicCamera->B(),
			m_OrtographicCamera->A()
		);

		glClear(GL_COLOR_BUFFER_BIT);
		
		glEnable(GL_BLEND);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

		// TODO: Have an active shader and sprite vertex array pointer?
		m_DefaultSpriteShader->SetActive();
		m_DefaultSpriteVertexArray->SetActive();

		// Camera
		Matrix4 ViewProj(m_OrtographicCamera->GetCameraViewProjection());
		m_DefaultSpriteShader->SetMatrixUniform("uViewProj", ViewProj);
		m_DefaultSpriteShader->SetColorUniform("uTintColor", m_White);

		while (!m_SpriteRenderDataQueue.empty()) {
			// Can this create a memory leak? =======================================
			SpriteRenderData RenderData = m_SpriteRenderDataQueue[0];
			m_SpriteRenderDataQueue.erase(m_SpriteRenderDataQueue.begin());
			// ======================================================================

			if (RenderData.Texture) {
				RenderData.Texture->SetWidth(RenderData.Width);
				RenderData.Texture->SetHeight(RenderData.Height);
				m_DefaultSpriteShader->SetColorUniform("uTintColor", RenderData._Color);

				Matrix4 TextureScale = Matrix4::CreateScale(
					static_cast<float>(RenderData.Texture->GetWidth()),
					static_cast<float>(RenderData.Texture->GetHeight()),
					1.0f
				);

				Matrix4 WorldScale = Matrix4::CreateScale(RenderData.Scale->x, RenderData.Scale->y, 1.0f);
				Matrix4 WorldRotation = Matrix4(glm::rotate(glm::mat4(1.0f), glm::radians(RenderData.Rotation), glm::vec3(0.0f, 0.0f, -1.0f)));
				Matrix4 WorldTranslation = Matrix4::CreateTranslation(RenderData.Position->x, RenderData.Position->y, 0.0f);

				Matrix4 World = (WorldTranslation * WorldRotation * WorldScale) * TextureScale;
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