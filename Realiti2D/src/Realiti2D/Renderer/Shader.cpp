#include "Shader.h"
#include "Realiti2D/Log.h"
#include "Color.h"

#include <fstream>
#include <sstream>

namespace Realiti2D {
	// ------------------------------------------------
	// Public
	// ------------------------------------------------
	Shader::Shader() : m_ShaderProgram(0), m_VertexShader(0), m_FragShader(0) { }
	Shader::~Shader() { }

	bool Shader::Load(const std::string& VertName, const std::string FragName) {
		if (
			!CompileShader(VertName, GL_VERTEX_SHADER, m_VertexShader) ||
			!CompileShader(FragName, GL_FRAGMENT_SHADER, m_FragShader)
			) {
			return false;
		}

		// Create a shader program that links together the vertex/frag shaders
		m_ShaderProgram = glCreateProgram();
		glAttachShader(m_ShaderProgram, m_VertexShader);
		glAttachShader(m_ShaderProgram, m_FragShader);
		glLinkProgram(m_ShaderProgram);

		if (!IsValidProgram()) {
			return false;
		}

		return true;
	}

	void Shader::Unload() {
		glDeleteProgram(m_ShaderProgram);
		glDeleteShader(m_VertexShader);
		glDeleteShader(m_FragShader);
	}

	void Shader::SetActive() {
		glUseProgram(m_ShaderProgram);
	}
	
	void Shader::SetMatrixUniform(const char* Name, const Matrix4& Matrix) {
		GLuint loc = glGetUniformLocation(m_ShaderProgram, Name);
		
		/* void glUniformMatrix4fv(	
				GLint location,
 				GLsizei count,
 				GLboolean transpose,
 				const GLfloat *value
		); */
		glUniformMatrix4fv(loc, 1, GL_FALSE, Matrix.GetAsFloatPointer());
	}

	void Shader::SetColorUniform(const char* Name, const Color* Color) {
		GLuint loc = glGetUniformLocation(m_ShaderProgram, Name);
		glUniform4fv(loc, 1, reinterpret_cast<const float*>((&Color->rgba)));
	}
	
	// ------------------------------------------------
	// Private
	// ------------------------------------------------
	bool Shader::CompileShader(const std::string& FileName, GLenum ShaderType, GLuint& OutShader) {
		std::ifstream ShaderFile(FileName);

		if (ShaderFile.is_open()) {
			std::stringstream sstream;
			sstream << ShaderFile.rdbuf();
			std::string contents = sstream.str();
			const char* ContentsChar = contents.c_str();

			OutShader = glCreateShader(ShaderType);
			glShaderSource(OutShader, 1, &ContentsChar, nullptr);
			glCompileShader(OutShader);

			if (!IsCompiled(OutShader)) {
				CORE_ERROR("[shader] failed to compile shader: {0}", FileName.c_str());
				return false;
			}
		}
		else {
			CORE_ERROR("[shader] shader file not found: {0}", FileName.c_str());
			return false;
		}

		return true;
	}

	bool Shader::IsCompiled(GLuint Shader) {
		GLint Status;
		glGetShaderiv(Shader, GL_COMPILE_STATUS, &Status);

		if (Status != GL_TRUE) {
			char Buffer[512];
			memset(Buffer, 0, 512);
			glGetShaderInfoLog(Shader, 511, nullptr, Buffer);
			CORE_WARNING("[shader] GLSL compile failed: {0}", Buffer);
			return false;
		}

		return true;
	}

	bool Shader::IsValidProgram() {
		GLint Status;
		glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &Status);

		if (Status != GL_TRUE) {
			char Buffer[512];
			memset(Buffer, 0, 512);
			glGetProgramInfoLog(m_ShaderProgram, 511, nullptr, Buffer);
			CORE_WARNING("[shader] SDL Link Status: {0}", Buffer);
			return false;
		}

		return true;


	}
}