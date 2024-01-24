#include "ResourceManager.h"


const Shader& ResourceManager::LoadShader(const char* vert, const char* frag) {
	return Shader(vert, frag);
}