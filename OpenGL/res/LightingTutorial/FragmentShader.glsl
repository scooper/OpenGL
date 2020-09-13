#version 330 core
out vec4 FragColour;

struct Material 
{
	sampler2D Diffuse;
	sampler2D Specular;
	float Shininess;
};

struct Light
{
	vec3 Position;
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;

	float Constant;
	float Linear;
	float Quadratic;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

void main()
{
	// phong model lighting calculations
	vec3 norm = normalize(Normal);

	// ambient
	vec3 ambient = light.Ambient * vec3(texture(material.Diffuse, TexCoords));
	
	// diffuse
	vec3 lightDir = normalize(light.Position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.Diffuse * diff * vec3(texture(material.Diffuse, TexCoords));

	// specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Shininess);
	vec3 specular =  light.Specular * spec * vec3(texture(material.Specular, TexCoords));

	float dist = length(light.Position - FragPos);
	float attenuation = 1.0 / (light.Constant + light.Linear + dist + light.Quadratic + (dist * dist));

	// result
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;


	FragColour = vec4(ambient + diffuse + specular, 1.0);
}