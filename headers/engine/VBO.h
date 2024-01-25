#ifndef VBO_H
#define VBO_H

#include "glad.h"

class VBO {
public:
	VBO() = delete;

	// Builds a VBO given a buffer type, handle, data, size of data, and usage
	static void BuildVBO(GLenum, unsigned int&, void*, unsigned int, GLenum);
	
	// Binds a VBO
	static void BindVBO(GLenum, unsigned int&);

	// Unbinds VBO
	static void UnBindVBO(GLenum);

	// Enables VBO, same paramters as glVertexAttribPointer
	static void EnableVBO(unsigned int, unsigned int, GLenum, GLboolean, GLsizei, const void*);
};

#endif // !VBO_H
