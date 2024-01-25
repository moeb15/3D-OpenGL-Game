#include "VBO.h"

void VBO::BuildVBO(GLenum type, unsigned int& handle,
	void* data, unsigned int size, GLenum usage) {
	glGenBuffers(1, &handle);
	glBindBuffer(type, handle);

	glBufferData(type, size, data, usage);
	glBindBuffer(type, handle);
}

void VBO::BindVBO(GLenum type, unsigned int& handle) {
	glBindBuffer(type, handle);
}

void VBO::UnBindVBO(GLenum type) {
	glBindBuffer(type, 0);
}

void VBO::EnableVBO(unsigned int index, unsigned int size, GLenum type,
	GLboolean normalized, GLsizei stride, const void* ptr) {
	glVertexAttribPointer(index, size, type, normalized, stride, ptr);
	glEnableVertexAttribArray(index);
}