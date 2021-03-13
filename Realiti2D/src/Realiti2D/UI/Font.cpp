#include <SDL.h>
#include "Font.h"
#include "Realiti2D/Log.h"
#include "Realiti2D/Renderer/Texture.h"

namespace Realiti2D {
	Font::Font() {}
	Font::~Font() {}

	bool Font::Load(const std::string& FileName) {
		std::vector<int> FontSizes = {
			8, 9,
			10, 11, 12, 14, 16, 18,
			20, 22, 24, 26, 28,
			30, 32, 34, 36, 38,
			40, 42, 44, 46, 48,
			52, 56,
			60, 64, 68,
			72
		};

		for (int size : FontSizes) {
			TTF_Font* f = TTF_OpenFont(FileName.c_str(), size);

			if (f == nullptr) {
				CORE_ERROR("Failed to load font {0} on size {1]", FileName, size);
				return false;
			}

			m_FontData.emplace(size, f);
		}
	}

	void Font::Unload() {
		for (auto& f : m_FontData) {
			TTF_CloseFont(f.second);
		}
	}

	Texture* Font::RenderTexture(const std::string& TextKey, int PointSize) {
		Texture* tex = nullptr;

		SDL_Color color;
		color.r = 255;
		color.g = 255;
		color.b = 255;
		color.a = 255;

		auto iter = m_FontData.find(PointSize);
		if (iter != m_FontData.end()) {
			TTF_Font* font = iter->second;

			SDL_Surface* surf = TTF_RenderUTF8_Blended(font, TextKey.c_str(), color);

			if (surf != nullptr) {
				tex = new Texture();
				tex->CreateFromSurface(surf);
				SDL_FreeSurface(surf);
			}
		}
		else {
			CORE_WARNING("Point size {0} is not supported", PointSize);
		}

		return tex;
	}
}