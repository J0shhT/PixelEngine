#version 450 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 textureCoord;

uniform mat4 worldViewMatrix;

out vec3 fragmentColor;
out vec2 texCoord;

void main(void)
{
	gl_Position = worldViewMatrix * vec4(vertexPosition, 1.0);

	fragmentColor = vertexColor;
	texCoord = textureCoord;
}