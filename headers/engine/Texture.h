#ifndef TEXTURE_H
#define TEXTURE_H

#include "stb_image.h"
#include "glad.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Texture {
public:
	unsigned int ID;

	Texture(){}
	~Texture();

	Texture(const char*);
	void activate(GLenum);
};

#endif