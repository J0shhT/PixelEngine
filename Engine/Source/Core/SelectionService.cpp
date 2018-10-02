/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Source/Core/SelectionService.cpp
*/

#include "Include/Core/SelectionService.h"

#include "Include/PixelError.h"
#include "Include/Core/PixelApp.h"

PIXEL_DECLARE_SINGLETON(Pixel::SelectionService);

Pixel::SelectionService::SelectionService()
{
	PIXEL_SINGLETON_CONSTRUCTOR(Pixel::SelectionService);
}

Pixel::SelectionService::~SelectionService()
{
	PIXEL_SINGLETON_DECONSTRUCTOR(Pixel::SelectionService);
}

void Pixel::SelectionService::SetSelection(std::weak_ptr<Pixel::Object::Object> object)
{
	_currentSelection = object;
	_hasSelection = true;
}

void Pixel::SelectionService::ResetSelection()
{
	_hasSelection = false;
}

bool Pixel::SelectionService::HasSelection()
{
	return _hasSelection;
}

void Pixel::SelectionService::SetSelectToolEnabled(bool enabled)
{

}

void Pixel::SelectionService::SetMoveToolEnabled(bool enabled)
{

}

void Pixel::SelectionService::SetSizeToolEnabled(bool enabled)
{

}

/*
void Pixel::SelectionService::Cut()
{

}
*/

void Pixel::SelectionService::Copy()
{
	if (HasSelection())
	{

	}
}

void Pixel::SelectionService::Paste()
{

}

void Pixel::SelectionService::Delete()
{
	if (HasSelection())
	{

	}
}

void Pixel::SelectionService::Duplicate()
{
	if (HasSelection())
	{

	}
}