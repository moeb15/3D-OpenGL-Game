#include "Shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::ifstream vertFile;
	std::stringstream vertContents;
	std::ifstream fragFile;
	std::stringstream fragContents;
	std::string vertStr;
	std::string fragStr;

	try {
		vertFile.open(vertexPath);
		vertContents << vertFile.rdbuf();

		vertFile.close();

		vertStr = vertContents.str();

		fragFile.open(fragmentPath);
		fragContents << fragFile.rdbuf();

		fragFile.close();

		fragStr = fragContents.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}

	const char* vertexShader = vertStr.c_str();
	const char* fragmentShader = fragStr.c_str();

	unsigned int vert;
	vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, 1, &vertexShader, NULL);
	glCompileShader(vert);

	int vertSuccess;
	char vertLog[512];

	glGetShaderiv(vert, GL_COMPILE_STATUS, &vertSuccess);
	if (!vertSuccess) {
		glGetShaderInfoLog(vert, 512, NULL, vertLog);
		std::cout << "Vertex shader failed to compile : " << vertLog << std::endl;
		return;
	}

	unsigned int frag;
	frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &fragmentShader, NULL);
	glCompileShader(frag);

	int fragSuccess;
	char fragLog[512];

	glGetShaderiv(frag, GL_COMPILE_STATUS, &fragSuccess);
	if (!fragSuccess) {
		glGetShaderInfoLog(frag, 512, NULL, fragLog);
		std::cout << "Fragment shader failed to compile : " << fragLog << std::endl;
		return;
	}
	
	ID = glCreateProgram();
	glAttachShader(ID, vert);
	glAttachShader(ID, frag);
	glLinkProgram(ID);

	int linkSuccess;
	char linkLog[512];
	
	glGetProgramiv(ID, GL_LINK_STATUS, &linkSuccess);
	if (!linkSuccess) {
		glGetProgramInfoLog(ID, 512, NULL, linkLog);
		std::cout << "Shader link error : " << linkLog << std::endl;
		return;
	}

	glDeleteShader(vert);
	glDeleteShader(frag);
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
		glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, glm::vec3 value) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value[0], value[1],
		value[2]);
}

Shader::~Shader() {
	glDeleteProgram(ID);
}