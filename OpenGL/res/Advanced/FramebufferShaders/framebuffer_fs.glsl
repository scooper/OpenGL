#version 330 core

out vec4 FragColour;

in vec2 TexCoords;

uniform sampler2D texture1;

void main() 
{
	FragColour = texture(texture1, TexCoords);
}