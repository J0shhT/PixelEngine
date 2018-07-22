#pragma once

#include "Include/Common.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>

#define PIXEL_OBJECT_CONSTRUCTOR(className) \
	_name = #className; \
	_id = boost::lexical_cast<std::string>(boost::uuids::random_generator()()); \
	_createdAt = std::chrono::high_resolution_clock::now();

#define PIXEL_OBJECT_DECONSTRUCTOR(className)

#define PIXEL_DEFINE_OBJECT(className) \
	public: \
		const char* GetType() const noexcept;

#define PIXEL_DECLARE_OBJECT(className) \
	const char* Pixel::Object::className::GetType() const noexcept \
	{ \
		return STRINGIFY(className); \
	}

/* Forward declaration for SceneManager */
namespace Pixel {
	class SceneManager;
}

#pragma warning(push)
#pragma warning(disable: 4251)

namespace Pixel::Object {

	/**
	*  TODO
	*/
	class PIXEL_API Object : public std::enable_shared_from_this<Object>
	{
		public:

			/**
			*  Class constructor
			*/
			Object();

			/**
			*  Class deconstructor
			*/
			virtual ~Object();

			/**
			*  Returns the type name of the object
			*/
			virtual const char* GetType() const noexcept;

			/**
			*  Returns the unique id representing this object
			*/
			std::string GetId() const;

			/**
			*  TODO
			*/
			double GetAge() const;

			/**
			*  TODO
			*/
			std::string GetName() const;

			/**
			*  TODO
			*/
			void SetName(const std::string&);

			/**
			*  TODO
			*/
			bool IsDeleted();

			/**
			*  TODO
			*/
			template<typename T> bool IsA();

		protected:

			friend class Pixel::SceneManager;

			/**
			*  The unique id representing this object
			*  This id is generated when the object is created
			*  See Object::GetId()
			*/
			std::string _id;

			/**
			*  The time that this object was created
			*  See Object::GetAge()
			*/
			std::chrono::time_point<std::chrono::steady_clock> _createdAt;

			/**
			*  Whether or not the object was deleted from it's scene
			*  See Pixel::SceneManager::DeleteObject()
			*/
			bool _isDeleted;

			/**
			*  The name for this object
			*  Names are not unique and multiple objects can 
			have the same name
			*  See Object::GetName() and Object::SetName()
			*/
			std::string _name;

	};

	template<typename T>
	bool Object::IsA()
	{
		return dynamic_cast<T*>(this) != nullptr;
	}

}

#pragma warning(pop)