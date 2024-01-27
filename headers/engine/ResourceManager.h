#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Shader.h"
#include "Texture.h"

class ResourceManager {
public:
	ResourceManager() = delete;

	// Loads a shader given the vertex and fragment shader file paths
	static const Shader& LoadShader(const char* vert, const char* frag);

	// Loads a texture given an image file path
	static const Texture& LoadTexture(const char* path);
};

#endif 