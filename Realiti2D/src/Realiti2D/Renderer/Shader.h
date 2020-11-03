#pragma once
#include <GL/glew.h>
#include <string>
#include "Realiti2D/Math/Math.h"

namespace Realiti2D {
	class Shader {
	public:
		Shader();
		~Shader();

		bool Load(const std::string& VertName, const std::string FragName);
		void Unload();
		void SetActive();
		void SetMatrixUniform(const char* Name, const Matrix4& Matrix);

	private:
		bool CompileShader(const std::string& FileName, GLenum ShaderType, GLuint& OutShader);
		bool IsCompiled(GLuint Shader);
		bool IsValidProgram();

	private:
		GLuint m_VertexShader;
		GLuint m_FragShader;
		GLuint m_ShaderProgram;
	};
}