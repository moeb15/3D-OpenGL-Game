#version 330 core
#define MAX_LIGHTS 128
out vec4 FragColor;

struct Material{
	sampler2D diffuseMap;
	sampler2D specularMap;
	sampler2D emissionMap;
	float shininess;
};

struct DirLight{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

uniform int lightCount;

uniform Material material;
uniform PointLight pointLights[MAX_LIGHTS];
uniform DirLight dirLight;

in vec2 TexCoords;
in vec3 fragPos;
in vec3 normal;
in vec3 lPos;

vec3 CalcPointLight(PointLight light);
vec3 CalcDirLight(DirLight light);

void main(){
	vec3 emission = vec3(texture(material.emissionMap,TexCoords));
	vec3 result = CalcDirLight(dirLight) + emission;
	
	for(int i = 0; i < lightCount; i++){
		result += CalcPointLight(pointLights[i]);
	}

	FragColor = vec4(result, 1.0);
}

vec3 CalcPointLight(PointLight light){
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance 
			+ light.quadratic * distance * distance);

	// ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuseMap, TexCoords));

	// diffuse
	vec3 lightDir = normalize(lPos - fragPos);
	vec3 norm = normalize(normal);
	float diff = max(dot(norm,lightDir),0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuseMap, TexCoords));;

	// specular
	vec3 viewDir = normalize(-fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir),0),
		material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.specularMap, TexCoords)));

	
	return (diffuse + specular + ambient) * attenuation;
}

vec3 CalcDirLight(DirLight light){
	vec3 lightDir = normalize(-light.direction);

	// ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuseMap, TexCoords));

	// diffuse
	vec3 norm = normalize(normal);
	float diff = max(dot(norm,lightDir),0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuseMap, TexCoords));;

	// specular
	vec3 viewDir = normalize(-fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir),0),
		material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.specularMap, TexCoords)));

	return ambient + diffuse + specular;
}