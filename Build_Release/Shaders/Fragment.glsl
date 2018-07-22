#version 450 core

//in vec3 fragmentColor;
//in vec2 texCoord;

out vec4 color;

//uniform sampler2D tex;
//uniform int hasTexture;

void main(void)
{
	/*
	if (hasTexture == 1)
	{
		color = texture(tex, texCoord) * vec4(fragmentColor, 1.0);
	}
	else
	{
		color = vec4(fragmentColor, 1.0);
	}
	*/

	color = vec4(1.0, 0.0, 0.0, 1.0);
}