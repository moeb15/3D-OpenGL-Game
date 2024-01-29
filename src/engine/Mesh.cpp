#include "Mesh.h"

namespace Models {
	Mesh::Mesh(std::vector<Vertex> v, std::vector<unsigned int> i,
		std::vector<Texture> t) :
		verticies(v),
		indicies(i),
		textures(t) {

		setupMesh();
	}

	void Mesh::setupMesh() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Vertex),
			&verticies[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int),
			&indicies[0], GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(void*)0);

		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(void*)offsetof(Vertex, Normal));

		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(void*)offsetof(Vertex, TexCoords));

		glBindVertexArray(0);
	}

	void Mesh::Draw(Shader& shader) {
		unsigned int diffuseNum = 1;
		unsigned int specularNum = 1;

		for (unsigned int i = 0; i < textures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			std::string number;
			std::string name = textures[i].type;
			if (name == "texture_diffuse") {
				number = std::to_string(diffuseNum++);
			}
			else if (name == "texture_specular") {
				number = std::to_string(specularNum++);
			}

			shader.setFloat("material." + name + number, i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		glActiveTexture(GL_TEXTURE0);

		//draw mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}