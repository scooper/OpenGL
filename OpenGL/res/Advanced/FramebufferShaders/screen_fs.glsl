#version 330 core

out vec4 FragColour;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float kernel[9];
uniform bool greyscale = false;

const float offset = 1.0 / 300.0;

void main() 
{
	
	vec2 offsets[9] = vec2[](
		vec2(-offset, offset),
		vec2(0.0, offset),
		vec2(offset, offset),
		vec2(-offset, 0.0),
		vec2(0.0, 0.0),
		vec2(offset, 0.0),
		vec2(-offset, -offset),
		vec2(0.0, -offset),
		vec2(offset, -offset)
	);

	vec3 col = vec3(0.0);

	for(int i = 0; i < 9; i++)
	{
		vec3 sampleTex = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
		col += sampleTex * kernel[i];
	}

	if(greyscale)
	{
		float weightedGrey =  0.2126 * col.r + 0.7152 * col.g + 0.0722 * col.b;
		FragColour = vec4(weightedGrey, weightedGrey, weightedGrey, 1.0);
	}
	else
	{
		FragColour = vec4(col, 1.0);
	}

	
}