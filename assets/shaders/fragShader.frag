#version 330 core
out vec4 FragColor;

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;

in vec3 fragPos;
in vec3 normal;
in vec3 lPos;

void main(){
	// ambient
	vec3 ambient = light.ambient * material.ambient;

	// diffuse
	vec3 lightDir = normalize(lPos - fragPos);
	vec3 norm = normalize(normal);
	float diff = max(dot(norm,lightDir),0);
	vec3 diffuse = light.diffuse*material.diffuse*diff;

	// specular
	vec3 viewDir = normalize(-fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir),0),
		material.shininess);
	vec3 specular = light.specular*(spec*material.specular);

	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result, 1.0);
}