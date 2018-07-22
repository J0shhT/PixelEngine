#include "Include/Object/RenderableObject.h"

#include "Include/PixelOutput.h"

PIXEL_DECLARE_OBJECT(RenderableObject);

Pixel::Object::RenderableObject::RenderableObject()
{
	PIXEL_OBJECT_CONSTRUCTOR(RenderableObject);
	glGenBuffers(1, &_vertexBufferId);
	glGenBuffers(1, &_colorBufferId);
	glGenBuffers(1, &_textureBufferId);
}

Pixel::Object::RenderableObject::~RenderableObject()
{
	glDeleteBuffers(1, &_vertexBufferId);
	glDeleteBuffers(1, &_colorBufferId);
	glDeleteBuffers(1, &_textureBufferId);
	PIXEL_OBJECT_DECONSTRUCTOR(RenderableObject);
}
