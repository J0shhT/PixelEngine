#pragma once

#include "Include/Common.h"

#include "Include/Object/GuiObject.h"

#include <GL/glew.h>
#include <GL/glut.h>

#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Pixel {

	/**
	*  TODO
	*/
	enum class FontFamily
	{
		Arial
	};

	/**
	*  TODO
	*/
	enum class FontSize
	{
		Size8 = 8u,
		Smallest = Size8,
		Size12 = 12u,
		Size14 = 14u,
		Size24 = 24u,
		Size48 = 48u,
		Size72 = 72u,
		Largest = Size72
	};

	namespace Graphics {

		/**
		*  TODO
		*/
		struct Character
		{
			GLuint textureId;
			glm::ivec2 size;
			glm::ivec2 bearing;
			GLuint advance;
		};

		struct Font
		{
			Pixel::FontFamily family;
			Pixel::FontSize size;
			std::map<GLchar, Pixel::Graphics::Character> characters;
		};

	}

}

namespace Pixel {

	/**
	*  TODO
	*/
	class PIXEL_API GuiService final
	{

		PIXEL_DEFINE_SINGLETON(Pixel::GuiService);

		public:

			/**
			*  Class constructor
			*/
			GuiService();

			/**
			*  Class deconstructor
			*/
			~GuiService();

			/**
			*  TODO
			*/
			const std::map<std::string, std::shared_ptr<Pixel::Object::GuiObject>>& GetGuiObjects() const;

			/**
			*  TODO
			*/
			std::shared_ptr<Pixel::Object::GuiObject> GetGuiObjectById(const std::string&) const;

			/**
			*  TODO
			*/
			//std::shared_ptr<Pixel::Object::GuiObject> GetGuiObjectByName(const std::string&) const;

			/**
			*  TODO
			*/
			bool DeleteGui(const std::string& objectId);

			/**
			*  TODO
			*/
			bool DeleteGui(std::shared_ptr<Pixel::Object::GuiObject> object);

			/**
			*  TODO
			*/
			template<typename T> std::shared_ptr<T> CreateGui();

		private:

			Pixel::Graphics::Font _loadFont(Pixel::FontFamily, Pixel::FontSize);
			std::map<Pixel::FontSize, Pixel::Graphics::Font> _loadFont(Pixel::FontFamily);
			void _loadFonts();

			FT_Library _freeType;
			std::map<Pixel::FontFamily, std::map<Pixel::FontSize, Pixel::Graphics::Font>> _loadedFonts;

			void _addGuiObject(std::shared_ptr<Pixel::Object::GuiObject>);
			std::map<std::string, std::shared_ptr<Pixel::Object::GuiObject>> _guiObjects;

	};

	template<typename T> std::shared_ptr<T> GuiService::CreateGui()
	{
		std::shared_ptr<T> object = std::make_shared<T>();
		std::ostringstream strStream;
		strStream << "GuiService::CreateGui() - GUI of type " << typeid(T).name() << " created at address " << object.get();
		Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Info, strStream.str().c_str());
		_addGuiObject(object);
		return object;
	}

}