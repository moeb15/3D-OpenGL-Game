#ifndef MDOEL_H
#define MODEL_H

#include "Mesh.h"
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>

namespace Models {
	class Model {
	public:
		std::vector<Texture> textures_loaded;

		Model() {}

		Model(const char* path) {
			loadModel(path);
		}

		void Draw(Shader& shader);

	private:
		// model data
		std::vector<Mesh> meshes;
		std::string directory;

		void loadModel(std::string path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat,
			aiTextureType type, std::string typeName);
	};
}
#endif // !MDOEL_H
