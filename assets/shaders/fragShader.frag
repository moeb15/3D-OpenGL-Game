#version 330 core
out vec4 FragColor;

uniform vec3 objColor;
uniform vec3 lightColor;

in vec3 fragPos;
in vec3 normal;
in vec3 lPos;

void main(){
	// ambient
	float ambientStrength = 0.25;
	vec3 ambient = ambientStrength * lightColor;

	// diffuse
	vec3 lightDir = normalize(lPos - fragPos);
	vec3 norm = normalize(normal);
	float diff = max(dot(norm,lightDir),0);
	vec3 diffuse = diff*lightColor;

	// specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(-fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir),0),32);
	vec3 specular = specularStrength*spec*lightColor;

	vec3 result = (ambient + diffuse + specular)*objColor;

	FragColor = vec4(result, 1.0);
}