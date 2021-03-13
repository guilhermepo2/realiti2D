#include "Texture.h"

#include "Realiti2D/Log.h"
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <SDL.h>

namespace Realiti2D {
	Texture::Texture() : m_TextureID(0), m_Width(0), m_Height(0) { }

	Texture::~Texture() { }

	bool Texture::Load(const std::string& fileName) {
		int channels = 0;
		unsigned char* Image = SOIL_load_image(fileName.c_str(), &m_Width, &m_Height, &channels, SOIL_LOAD_AUTO);

		if (Image == nullptr) {
			CORE_ERROR("[texture] failed to load image {0}: {1}", fileName.c_str(), SOIL_last_result());
			return false;
		}

		int format = GL_RGB;
		if (channels == 4) {
			format = GL_RGBA;
		}

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, Image);

		SOIL_free_image_data(Image);

		// enabling bilinear filtering
		// maybe have an option to disable this?
		// since its a 2D engine pixel art is a thing and bilinear filtering destroys pixel art?

		// TODO: Have an if/else here...
		// blend
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// nearest neighbor
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		return true;
	}

	void Texture::Unload() {
		glDeleteTextures(1, &m_TextureID);
	}

	void Texture::SetActive() {
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void Texture::CreateFromSurface(SDL_Surface* surface) {
		m_Width = surface->w;
		m_Height = surface->h;

		// Generate a GL Texture
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
}