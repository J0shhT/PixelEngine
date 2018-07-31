#pragma once

#include "Include/Common.h"

#include "Include/Object/Object.h"

#pragma warning(push)
#pragma warning(disable: 4251)

namespace Pixel {

	/**
	*  TODO
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
			*  TODO
			*/
			const std::map<std::string, std::shared_ptr<Pixel::Object::Object>>& GetObjects() const;

			/**
			*  TODO
			*/
			std::shared_ptr<Pixel::Object::Object> GetObjectById(const std::string&) const;

			/**
			*  TODO
			*/
			//std::shared_ptr<Pixel::Object::Object> GetObjectByName(const std::string&) const;

			/**
			*  TODO
			*/
			bool DeleteObject(const std::string& objectId);

			/**
			*  TODO
			*/
			bool DeleteObject(std::shared_ptr<Pixel::Object::Object> object);

			/**
			*  TODO
			*/
			template<typename T> std::shared_ptr<T> CreateObject();

		private:

			void _addObject(std::shared_ptr<Pixel::Object::Object>);

			std::map<std::string, std::shared_ptr<Pixel::Object::Object>> _objects;

	};

	template<typename T> std::shared_ptr<T> SceneManager::CreateObject()
	{
		std::shared_ptr<T> object = std::make_shared<T>();
		_addObject(object);
		return object;
	}

}

#pragma warning(pop)