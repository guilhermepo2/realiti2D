#include "VertexArray.h"
#include <GL/glew.h>

namespace Realiti2D {

	VertexArray::VertexArray(const float* Verts, unsigned int NumVerts, const unsigned int* Indices, unsigned int NumIndices) 
		: m_NumberOfVertices(NumVerts),
		m_NumberOfIndices(NumIndices) {

		// Create the vertex array object and store its ID in the m_VertexArrayOpenGLID Variable
		glGenVertexArrays(1, &m_VertexArrayOpenGLID);
		glBindVertexArray(m_VertexArrayOpenGLID);

		// Create a vertex buffer
		glGenBuffers(1, &m_VertexBufferOpenGLID);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferOpenGLID);
		/* void glBufferData(	
				GLenum target,
 				GLsizeiptr size,
 				const void * data,
 				GLenum usage
		); */
		glBufferData( GL_ARRAY_BUFFER, NumVerts * ( 5 * sizeof(float) ), Verts, GL_STATIC_DRAW );

		// Create Index Buffer
		glGenBuffers( 1, &m_IndexBufferOpenGLID );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferOpenGLID );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, NumIndices * sizeof(unsigned int), Indices, GL_STATIC_DRAW );

		// Specify the Vertex Attribute
		// 3 Attributes for the Position and 2 Attributes for Normal Coordinates
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<void*>( sizeof(float) * 3 ) );
	}
	
	VertexArray::~VertexArray() {
		glDeleteBuffers( 1, &m_VertexBufferOpenGLID );
		glDeleteBuffers( 1, &m_IndexBufferOpenGLID );
		glDeleteBuffers( 1, &m_VertexArrayOpenGLID );
	}
	
	void VertexArray::SetActive() {
		glBindVertexArray( m_VertexArrayOpenGLID );
	}

}