#include "Include/Core/SelectionService.h"

#include "Include/PixelError.h"
#include "Include/Core/PixelApp.h"

Pixel::SelectionService::SelectionService()
{
	assert(Pixel::SelectionService::instance == nullptr);
	if (Pixel::SelectionService::instance != nullptr)
		throw Pixel::Exception::FatalError("Failed to create Pixel::SelectionService because a singleton instance already exists");
	Pixel:SelectionService::instance = this;
}

Pixel::SelectionService::~SelectionService()
{
	Pixel:SelectionService::instance = nullptr;
}

Pixel::SelectionService* Pixel::SelectionService::instance = nullptr;
Pixel::SelectionService* Pixel::SelectionService::Singleton()
{
	assert(Pixel::SelectionService::instance != nullptr);
	if (Pixel::SelectionService::instance == nullptr)
		throw Pixel::Exception::FatalError("Failed to get Pixel::SelectionService singleton because instance does not exist");
	return Pixel::SelectionService::instance;
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

