#version 330 core
layout (location = 0) in vec3 objPos;
layout (location = 0) in vec3 objNorm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;

out vec3 fragPos;
out vec3 normal;
out vec3 lPos;


void main(){
	gl_Position = projection * view * model * vec4(objPos, 1.0);
	normal = mat3(transpose(inverse(view * model))) * objNorm;
	fragPos = vec3(view * model * vec4(objPos, 1.0));
	lPos = vec3(view * vec4(lightPos,1.0));
}