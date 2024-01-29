#ifndef MESH_H
#define MESH_H

#include "glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include "Shader.h"

namespace Models {
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	struct Texture {
		unsigned int id;
		std::string type;
		std::string path;
	};

	class Mesh {
	public:
		// mesh data
		std::vector<Vertex> verticies;
		std::vector<unsigned int> indicies;
		std::vector<Texture> textures;

		Mesh(std::vector<Vertex>, std::vector<unsigned int>,
			std::vector<Texture>);
		void Draw(Shader& shader);

	private:
		// render data
		unsigned int VAO, VBO, EBO;

		void setupMesh();

	};
}
#endif // !MESH_H*/
