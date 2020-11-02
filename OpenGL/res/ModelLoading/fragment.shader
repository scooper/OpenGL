#version 330 core
out vec4 FragColour;

struct Material
{
	//
	sampler2D textureDiffuse1;
	//sampler2D textureDiffuse2;
	sampler2D textureSpecular1;
	//sampler2D textureSpecular2;
	float Shininess;
};

struct DirLight
{
	vec3 Direction;
	vec3 Diffuse;
};

struct PointLight
{
	vec3 Position;
	vec3 Diffuse;

	float Constant;
	float Linear;
	float Quadratic;
};

uniform Material material;
uniform DirLight dirLight;
// max 32 lights in a scene
#define N_POINT_LIGHTS 32
uniform int nPointLights;
uniform PointLight pointLights[N_POINT_LIGHTS];
uniform vec3 viewPos;
uniform vec3 Ambient;

in vec3 Normal;
in vec3 FragPos;
in vec2 UV;

vec3 CalcDirLight(vec3 viewDir)
{
	vec3 lightDir = normalize(-dirLight.Direction);

	// ambient

	// diffuse
	float diff = max(dot(Normal, lightDir), 0.0);
	vec3 diffuse = dirLight.Diffuse * diff * vec3(texture(material.textureDiffuse1, UV));
	// specular
	vec3 reflectDir = reflect(-lightDir, Normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Shininess);
	vec3 specular = 1.0 * spec * vec3(texture(material.textureSpecular1, UV));


	return (diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 viewDir)
{
	// diffuse
	vec3 lightDir = normalize(light.Position - FragPos);
	float diff = max(dot(Normal, lightDir), 0.0);
	vec3 diffuse = light.Diffuse * diff * vec3(texture(material.textureDiffuse1, UV));

	// specular
	float specularStrength = 0.5;
	vec3 reflectDir = reflect(-lightDir, Normal);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Shininess);
	vec3 specular = 1.0 * spec * vec3(texture(material.textureSpecular1, UV));

	float dist = length(light.Position - FragPos);
	float attenuation = 1.0 / (light.Constant + light.Linear + dist + light.Quadratic + (dist * dist));

	// result
	diffuse *= attenuation;
	specular *= attenuation;

	return (diffuse + specular);
}

void main()
{
	vec3 viewDir = normalize(viewPos - FragPos);

	// ambient initial value
	vec3 result = Ambient * vec3(texture(material.textureDiffuse1, UV));
	// dir light (sun)
	result += vec3(CalcDirLight(viewDir));
	// limit to passed in N uniform (so we're not pointlessly calculating)
	for (int i = 0; i < nPointLights; i++)
	{
		result += CalcPointLight(pointLights[i], viewDir);
	}

	FragColour = vec4(result, 1.0);
}