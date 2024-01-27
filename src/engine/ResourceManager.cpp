#include "ResourceManager.h"


const Shader& ResourceManager::LoadShader(const char* vert, const char* frag) {
	return Shader(vert, frag);
}

const Texture& ResourceManager::LoadTexture(const char* path) {
	return Texture(path);
}