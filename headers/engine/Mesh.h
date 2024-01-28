#ifndef MESH_H
#define MESH_H

#include "glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include "Shader.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct TextureStruct {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
public:
	// mesh data
	std::vector<Vertex> verticies;
	std::vector<unsigned int> indicies;
	std::vector<TextureStruct> textures;

	Mesh(std::vector<Vertex>, std::vector<unsigned int>,
		std::vector<TextureStruct>);
	void Draw(Shader& shader);
	
private:
	// render data
	unsigned int VAO, VBO, EBO;

	void setupMesh();

};

#endif // !MESH_H
