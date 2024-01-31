#include "ResourceManager.h"
#include "Model.h"

const Shader& ResourceManager::LoadShader(const char* vert, const char* frag) {
	return Shader(vert, frag);
}

const Texture& ResourceManager::LoadTexture(const char* path) {
	return Texture(path);
}

Models::Model ResourceManager::LoadModel(const char* path) {
	return Models::Model(path);
}