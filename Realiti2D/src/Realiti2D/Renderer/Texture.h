#pragma once
#include <string>

namespace Realiti2D {
	class Texture {
	public:
		Texture();
		~Texture();

		bool Load(const std::string& fileName);
		void Unload();
		void SetActive();

		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }
		void SetWidth(int value) { m_Width = value; }
		void SetHeight(int value) { m_Height = value; }

	private:
		unsigned int m_TextureID;
		int m_Width;
		int m_Height;
	};
}