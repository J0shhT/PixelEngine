#include "Include/Object/GuiObject.h"

#include "Include/PixelOutput.h"

PIXEL_DECLARE_OBJECT(GuiObject);

Pixel::Object::GuiObject::GuiObject()
{
	PIXEL_OBJECT_CONSTRUCTOR(GuiObject);
	_isVisible = true;
}

Pixel::Object::GuiObject::~GuiObject()
{
	PIXEL_OBJECT_DECONSTRUCTOR(GuiObject);
}

void Pixel::Object::GuiObject::SetVisible(bool value)
{
	_isVisible = value;
}

bool Pixel::Object::GuiObject::IsVisible() const
{
	return _isVisible;
}
