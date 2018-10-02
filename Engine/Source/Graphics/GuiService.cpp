/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Source/Graphics/GuiService.cpp
*/

#include "Include/Graphics/GuiService.h"

#include "Include/PixelError.h"

#include "Include/Graphics/RenderService.h"

PIXEL_DECLARE_SINGLETON(Pixel::GuiService);

Pixel::GuiService::GuiService()
{
	PIXEL_SINGLETON_CONSTRUCTOR(Pixel::GuiService);
	/*
	if (FT_Init_FreeType(&_freeType))
	{
		PixelFatalError("Failed to initialize FreeType library");
	}
	_loadFonts();
	*/
}

Pixel::GuiService::~GuiService()
{
	/*
	if (FT_Done_FreeType(_freeType))
	{
		PixelFatalError("Failed to destroy FreeType library");
	}
	*/
	PIXEL_SINGLETON_DECONSTRUCTOR(Pixel::GuiService);
}

const std::map<std::string, std::shared_ptr<Pixel::Object::GuiObject>>& Pixel::GuiService::GetGuiObjects() const
{
	return _guiObjects;
}

std::shared_ptr<Pixel::Object::GuiObject> Pixel::GuiService::GetGuiObjectById(const std::string& id) const
{
	if (_guiObjects.count(id) > 0)
	{
		return _guiObjects.at(id);
	}
	return nullptr;
}

std::shared_ptr<Pixel::Object::GuiObject> Pixel::GuiService::GetGuiObjectByName(const std::string& name) const
{
	for (auto iter = _guiObjects.cbegin(); iter != _guiObjects.cend(); iter++)
	{
		if (iter->second->GetName() == name)
		{
			return iter->second;
		}
	}
	return nullptr;
}

size_t Pixel::GuiService::GetGuiObjectCount() const
{
	return _guiObjects.size();
}

bool Pixel::GuiService::DeleteGui(const std::string& objectId)
{
	if (GetGuiObjectById(objectId) != nullptr)
	{
		auto object = _guiObjects.at(objectId);
		_guiObjects.erase(objectId);
		object->_isDeleted = true;
		object.reset();
		return true;
	}
	return false;
}

bool Pixel::GuiService::DeleteGui(std::shared_ptr<Pixel::Object::GuiObject> object)
{
	return DeleteGui(object->GetId());
}

/*
Pixel::Graphics::Font Pixel::GuiService::_loadFont(Pixel::FontFamily fontFamily, Pixel::FontSize fontSize)
{
	std::string fontFilePath = "";
#ifdef _DEBUG
	fontFilePath = "J:/PixelEngine/Dev/Release/"; ///todo
#endif
	switch (fontFamily)
	{
		case Pixel::FontFamily::Arial:
			fontFilePath = fontFilePath + "Content/Fonts/arial.ttf";
			break;

		default:
			PixelFatalError("GuiService failed to load font of unknown FontFamily " + std::to_string((int)fontFamily));
			fontFilePath = fontFilePath + "Content/Fonts/arial.ttf";
			break;
	}

	FT_Face face;
	if (FT_New_Face(_freeType, fontFilePath.c_str(), 0, &face))
	{
		PixelFatalError("GuiService failed to load font face \"" + fontFilePath + "\"");
	}
	FT_Set_Pixel_Sizes(face, 0u, (FT_UInt)fontSize);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	Pixel::Graphics::Font font = {
		fontFamily,
		fontSize,
		std::map<GLchar, Pixel::Graphics::Character>()
	};

	for (GLubyte c = 0; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			PixelError("GuiService failed to load font character " + std::to_string(c) + " for \"" + fontFilePath + "\"");
			continue;
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Pixel::Graphics::Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		
		font.characters.insert(std::pair<GLchar, Pixel::Graphics::Character>(c, character));

	}

	FT_Done_Face(face);

	Pixel::StandardOut::Singleton()->Printf(Pixel::OutputType::Info, "GuiService loaded font \"%s\" (size %d)", fontFilePath.c_str(), (int)fontSize);

	return font;
}
*/

/*
std::map<Pixel::FontSize, Pixel::Graphics::Font> Pixel::GuiService::_loadFont(Pixel::FontFamily fontFamily)
{
	auto fontMap = std::map<Pixel::FontSize, Pixel::Graphics::Font>();

	fontMap[Pixel::FontSize::Size8] = _loadFont(fontFamily, Pixel::FontSize::Size8);
	fontMap[Pixel::FontSize::Size12] = _loadFont(fontFamily, Pixel::FontSize::Size12);
	fontMap[Pixel::FontSize::Size14] = _loadFont(fontFamily, Pixel::FontSize::Size14);
	fontMap[Pixel::FontSize::Size24] = _loadFont(fontFamily, Pixel::FontSize::Size24);
	fontMap[Pixel::FontSize::Size48] = _loadFont(fontFamily, Pixel::FontSize::Size48);
	fontMap[Pixel::FontSize::Size72] = _loadFont(fontFamily, Pixel::FontSize::Size72);

	return fontMap;
}
*/

/*
void Pixel::GuiService::_loadFonts()
{
	_loadedFonts[Pixel::FontFamily::Arial] = _loadFont(Pixel::FontFamily::Arial);
}
*/

void Pixel::GuiService::_addGuiObject(std::shared_ptr<Pixel::Object::GuiObject> object)
{
	if (!object->IsA<Pixel::Object::GuiObject>())
	{
		PixelFatalError("GuiService attempted to create non-GUI object");
		return;
	}
	_guiObjects[object->GetId()] = object;
}