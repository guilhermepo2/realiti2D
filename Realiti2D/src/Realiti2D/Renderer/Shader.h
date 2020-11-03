#pragma once
#include <GL/glew.h>
#include <string>

namespace Realiti2D {
	class Shader {
	public:
		Shader();
		~Shader();

		bool Load(const std::string& VertName, const std::string FragName);
		void Unload();
		void SetActive();
		
		// TODO: Matrix4
		// void SetMatrixUniform(const char* Name, const Matrix)

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