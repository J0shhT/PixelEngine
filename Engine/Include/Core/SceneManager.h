/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Core/SceneManager.h
*/

#pragma once

#include "Include/Common.h"

#include "Include/Object/Object.h"

/**
*  Argument 1: The object classname to create that is inside the namespace Pixel::Object
*  Returns a shared_ptr to the object created
*/
#define PixelCreateObject(type) Pixel::SceneManager::Singleton()->CreateObject<Pixel::Object:: ## type>();

/**
*  Argument 1: shared_ptr to a class that inherits from Pixel::Object::Object
*  Removes the specified object from the game scene and marks it as deleted.
*  This macro also frees the ownership of the shared_ptr given to the macro.
*/
#define PixelDeleteObject(obj) if (Pixel::SceneManager::Singleton()->DeleteObject(obj)) { obj.reset(); }

#pragma warning(push)
#pragma warning(disable: 4251)

namespace Pixel {

	/**
	*  The Pixel::SceneManager is a singleton service used to
	manage all the game objects in the game and is used to create
	new objects or delete existing objects.
	*  Game objects must be created and destroyed using this service.
	*  If game objects are not created using this service, they will not
	be properly visible to other systems in Pixel Engine.
	*  If game objects are not destroyed using this service, they will not 
	be properly deleted and will cause undefined behavior.
	*/
	class PIXEL_API SceneManager final
	{

		PIXEL_DEFINE_SINGLETON(Pixel::SceneManager);

		public:

			/**
			*  Class constructor
			*/
			SceneManager();

			/**
			*  Class deconstructor
			*/
			~SceneManager();

			/**
			*  Returns a const reference to an std::map of all game objects.
			*  The key of the std::map is a std::string of the unique id for
			the game object.
			*  The value of the std::map is a std::shared_ptr of the
			game object, as a Pixel::Object::Object
			*/
			const std::map<std::string, std::shared_ptr<Pixel::Object::Object>>& GetObjects() const;

			/**
			*  Returns the game object with the specified unique object id.
			*  Returns nullptr if the game object is not found.
			*/
			std::shared_ptr<Pixel::Object::Object> GetObjectById(const std::string&) const;

			/**
			*  Returns the first game object with the specified object name.
			*  If multiple objects have the same name, it will only return the
			first one it comes across in the search.
			*  See Pixel::Object::Object::SetName()
			*/
			std::shared_ptr<Pixel::Object::Object> GetObjectByName(const std::string&) const;

			/**
			*  Returns the number of game objects in the game.
			*/
			size_t GetObjectCount() const;

			/**
			*  Deletes the game object with the specified unique object id.
			*  Returns true if the object was deleted, false otherwise.
			*/
			bool DeleteObject(const std::string& objectId);

			/**
			*  Deletes the specified game object.
			*  Returns true if the object was deleted, false otherwise.
			*  Consider using the macro PixelDeleteObject() instead of
			calling this function directly.
			*/
			bool DeleteObject(std::shared_ptr<Pixel::Object::Object> object);

			/**
			*  Creates a game object of the specified type.
			*  Any class type can be created as a game object, but
			anything that is outside Pixel::Object is undefined behavior.
			*  Consider using the macro PixelCreateObject() instead of
			calling this function directly.
			*/
			template<typename T> std::shared_ptr<T> CreateObject();

		private:

			void _addObject(std::shared_ptr<Pixel::Object::Object>);
			std::map<std::string, std::shared_ptr<Pixel::Object::Object>> _objects;

	};

	template<typename T> std::shared_ptr<T> SceneManager::CreateObject()
	{
		std::shared_ptr<T> object = std::make_shared<T>();
		std::ostringstream strStream;
		strStream << "SceneManager::CreateObject() - Object of type " << typeid(T).name() << " created at address " << object.get();
		Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Info, strStream.str().c_str());
		_addObject(object);
		return object;
	}

}

#pragma warning(pop)