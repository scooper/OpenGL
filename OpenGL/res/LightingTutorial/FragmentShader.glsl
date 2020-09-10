#version 330 core
out vec4 FragColour;

struct Material 
{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	float Shininess;
};

struct Light
{
	vec3 Position;
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;

void main()
{
	// phong model lighting calculations
	vec3 norm = normalize(Normal);

	// ambient
	vec3 ambient = material.Ambient * light.Ambient;
	
	// diffuse
	vec3 lightDir = normalize(light.Position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.Diffuse * (diff * material.Diffuse);

	// specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Shininess);
	vec3 specular =  light.Specular * (material.Specular * spec);

	// result
	vec3 result = ambient + diffuse + specular;

	FragColour = vec4(result, 1.0);
}