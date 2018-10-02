/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Graphics/GuiService.h
*/

#pragma once

#include "Include/Common.h"

#include "Include/Object/GuiObject.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>

/**
*  Argument 1: The gui object classname to create that is inside the namespace Pixel::Object
*  Returns a shared_ptr to the gui object created
*/
#define PixelCreateGui(type) Pixel::GuiService::Singleton()->CreateGui<Pixel::Object:: ## type>();

/**
*  Argument 1: shared_ptr to a class that inherits from Pixel::Object::GuiObject
*  Removes the specified object from the GuiService and marks it as deleted.
*  This macro also frees the ownership of the shared_ptr given to the macro.
*/
#define PixelDeleteGui(obj) if (Pixel::GuiService::Singleton()->DeleteGui(obj)) { obj.reset(); }

#pragma warning(push)
#pragma warning(disable: 4251)

namespace Pixel {

	/**
	*  The Pixel::GuiService is a singleton service used to
	manage all the gui objects in the game and is used to create
	new gui objects or delete existing gui objects.
	*  Gui objects must be created and destroyed using this service.
	*  If gui objects are not created using this service, they will not
	be properly visible to other systems in Pixel Engine.
	*  If gui objects are not destroyed using this service, they will not 
	be properly deleted and will cause undefined behavior.
	*  The Pixel::SceneManager cannot be used to make gui objects.
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
			*  Returns a const reference to an std::map of all gui objects.
			*  The key of the std::map is a std::String of the unique id for
			the gui object.
			*  The value of the std::map is a std::shared_ptr of the
			gui object, as a Pixel::Object::GuiObject
			*/
			const std::map<std::string, std::shared_ptr<Pixel::Object::GuiObject>>& GetGuiObjects() const;

			/**
			*  Returns the gui object with the specified unique object id.
			*  Returns nullptr if the gui object is not found.
			*/
			std::shared_ptr<Pixel::Object::GuiObject> GetGuiObjectById(const std::string&) const;

			/**
			*  Returns the first gui object with the specified object name.
			*  If multiple objects have the same name, it will only return the
			first one it comes across in the search.
			*  See Pixel::Object::Object::SetName()
			*/
			std::shared_ptr<Pixel::Object::GuiObject> GetGuiObjectByName(const std::string&) const;

			/**
			*  Returns the number of gui objects in the game.
			*/
			size_t GetGuiObjectCount() const;

			/**
			*  Deletes the gui object with the specified unique object id.
			*  Returns true if the object was deleted, false otherwise.
			*/
			bool DeleteGui(const std::string& objectId);

			/**
			*  Deletes the specified gui object.
			*  Returns true if the object was deleted, false otherwise. 
			*  Consider using the macro PixelDeleteGui() instead of
			calling this function directly.
			*/
			bool DeleteGui(std::shared_ptr<Pixel::Object::GuiObject> object);

			/**
			*  Creates a gui object of the specified type.
			*  Any class type can be created as a gui object, but
			anything that does not inheriet from Pixel::Object::GuiObject
			well result in undefined behavior.
			*  Consider using the macro PixelCreateGui() instead of
			calling this function directly.
			*/
			template<typename T> std::shared_ptr<T> CreateGui();

		private:

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

#pragma warning(pop)