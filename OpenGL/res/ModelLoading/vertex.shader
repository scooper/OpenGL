#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 mvp;

out vec3 FragPos;
out vec3 Normal;
out vec2 UV;

void main()
{
	FragPos = vec3(modelMatrix * vec4(pos, 1.0));
	Normal = normalize(mat3(transpose(inverse(modelMatrix))) * normal);
	UV = uv;

	gl_Position = mvp * vec4(FragPos, 1.0);
}