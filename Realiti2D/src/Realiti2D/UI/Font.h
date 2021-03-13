#pragma once
#include <SDL_ttf.h>
#include <string>
#include <unordered_map>

namespace Realiti2D {
	
	class Texture;

	class Font {
	public:
		Font();
		~Font();

		bool Load(const std::string& FileName);
		void Unload();
		Texture* RenderTexture(const std::string& TextKey, int PointSize = 30);

	private:
		std::unordered_map<int, TTF_Font*> m_FontData;
	};
}