#pragma once

namespace Realiti2D {
	class VertexArray {
	public:
		VertexArray(const float* Verts, unsigned int NumVerts, const unsigned int* Indices, unsigned int NumIndices);
		~VertexArray();
		void SetActive();

		unsigned int GetNumIndices()	const { return m_NumberOfIndices; }
		unsigned int GetNumVertices()	const { return m_NumberOfVertices; }

	private:
		unsigned int m_NumberOfVertices;
		unsigned int m_NumberOfIndices;

		unsigned int m_VertexBufferOpenGLID;
		unsigned int m_IndexBufferOpenGLID;
		unsigned int m_VertexArrayOpenGLID;
	};
}