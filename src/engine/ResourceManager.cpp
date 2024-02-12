#include "ResourceManager.h"
#include "Model.h"


void ResourceManager::AddShader(ResourceTags::Shaders shaderTag, const char* vert, const char* frag) {
	std::unique_ptr<Shader> shader(
		new Shader(vert, frag));

	m_Shaders.insert(std::make_pair(shaderTag, std::move(shader)));
}

void ResourceManager::AddTexture(ResourceTags::Textures textureTag, const char* path) {
	std::unique_ptr<Texture> texture(
		new Texture(path));

	m_Textures.insert(std::make_pair(textureTag, std::move(texture)));
}

void ResourceManager::AddModel(ResourceTags::Models modelTag, const char* path) {
	std::unique_ptr<Models::Model> model(
		new Models::Model(path));

	m_Models.insert(std::make_pair(modelTag, std::move(model)));
}

const Shader& ResourceManager::LoadShader(ResourceTags::Shaders shaderTag) {
	auto kvPair = m_Shaders.find(shaderTag);
	if(kvPair == m_Shaders.end()){
		throw std::runtime_error("ResourceManager::LoadShader failed to load shader: " 
			+ std::to_string(shaderTag));
	}
	return *kvPair->second;
}

const Texture& ResourceManager::LoadTexture(ResourceTags::Textures textureTag) {
	auto kvPair = m_Textures.find(textureTag);
	if (kvPair == m_Textures.end(textureTag)) {
		throw std::runtime_error("ResourceManager::LoadTexture failed to load texture: "
			+ std::to_string(textureTag));
	}
	return *kvPair->second;
}

const Models::Model& ResourceManager::LoadModel(ResourceTags::Models modelTag) {
	auto kvPair = m_Models.find(modelTag);
	if (kvPair == m_Models.end()) {
		throw std::runtime_error("ResourceManager::LoadModel failed to load mode: "
			+ std::to_string(modelTag));
	}
	return *kvPair->second;
}