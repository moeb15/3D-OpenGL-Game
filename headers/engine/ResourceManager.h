#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Shader.h"
#include "Texture.h"
#include "ResourceTags.h"
#include <unordered_map>
#include <memory>

namespace Models {
	class Model;
}

class ResourceManager {
private:
	std::unordered_map<ResourceTags::Textures, std::unique_ptr<Texture>> m_Textures;
	std::unordered_map<ResourceTags::Shaders, std::unique_ptr<Shader>> m_Shaders;
	std::unordered_map<ResourceTags::Models, std::unique_ptr<Models::Model>> m_Models;

public:
	// Adds a shader given the shader tag, and the vertex and fragment shader file paths
	void AddShader(ResourceTags::Shaders shaderTag, const char* vert, const char* frag);

	// Adds a texture given the texture tag and an image file path
	void AddTexture(ResourceTags::Textures textureTag, const char* path);

	// Adds a model fiven the model tag and the model file path
	void AddModel(ResourceTags::Models modelTag, const char* path);

	// Loads a shader given the shader tag
	const Shader& LoadShader(ResourceTags::Shaders shaderTag);

	// Loads a texture given a texture tag
	const Texture& LoadTexture(ResourceTags::Textures textureTag);

	// Loads a model given the model tag
	const Models::Model& LoadModel(ResourceTags::Models modelTag);

};

#endif 