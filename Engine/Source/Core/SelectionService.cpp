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

void Pixel::SelectionService::SetSelection(void)
{

}

void Pixel::SelectionService::EnableSelectTool(bool enabled)
{

}

void Pixel::SelectionService::EnableMoveTool(bool enabled)
{

}

void Pixel::SelectionService::EnableSizeTool(bool enabled)
{

}

void Pixel::SelectionService::Cut()
{

}

void Pixel::SelectionService::Copy()
{

}

void Pixel::SelectionService::Paste()
{

}

void Pixel::SelectionService::Delete()
{

}

void Pixel::SelectionService::Duplicate()
{

}