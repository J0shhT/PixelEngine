/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Object/Object.h
*/

#pragma once

#include "Include/Common.h"

#include "Include/Core/EventManager.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>

/**
*  Common code to be called in every game object class constructor.
*  Internal usage only, unless you are creating your own object class.
*/
#define PIXEL_OBJECT_CONSTRUCTOR(className) \
	_name = #className; \
	_id = boost::lexical_cast<std::string>(boost::uuids::random_generator()()); \
	_createdAt = std::chrono::high_resolution_clock::now();

/**
*  Common code to be called in every game object class deconstructor.
*  Internal usage only, unless you are creating your own object class.
*/
#define PIXEL_OBJECT_DECONSTRUCTOR(className)

/**
*  Common members to be defined in all game object classes.
*  Internal usage only, unless you are creating your own object class.
*/
#define PIXEL_DEFINE_OBJECT(className) \
	public: \
		const char* GetType() const noexcept;

/**
*  Common members to be declared in all game object classes.
*  Internal usage only, unless you are creating your own object class.
*/
#define PIXEL_DECLARE_OBJECT(className) \
	const char* Pixel::Object::className::GetType() const noexcept \
	{ \
		return STRINGIFY(className); \
	}

/* Forward declarations */
namespace Pixel {
	class SceneManager;
	class GuiService;
}

#pragma warning(push)
#pragma warning(disable: 4251)

namespace Pixel::Object {

	/**
	*  The Object::Object game object is the base object
	class for all game objects in Pixel Engine.

	*  All game objects inherit from Object::Object.

	*  You can call the Object::GetType() virtual function on
	any game object to get what exact type of game object
	it is, if the object was casted down to an Object::Object.
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
			*  Returns the type name of the object.
			*/
			virtual const char* GetType() const noexcept;

			/**
			*  Returns the unique id representing this object.
			*/
			std::string GetId() const;

			/**
			*  Binds the specified EventType to the given event callback 
			function on this game object.
			*  Returns a unique id representing this binded event to
			use for unbinding.
			*/
			Pixel::EventCallbackId Bind(Pixel::EventType, Pixel::EventCallback*);

			/**
			*  Unbunds the specified EventType under the given unique event id.
			*/
			void Unbind(Pixel::EventType, Pixel::EventCallbackId);

			/**
			*  Returns the number of seconds that this object has existed for.
			*/
			double GetAge() const;

			/**
			*  Returns the name of this object.
			*  See Object::SetName()
			*/
			std::string GetName() const;

			/**
			*  Sets a name for this object.
			*  Names do not have to be unique.
			*/
			void SetName(const std::string&);

			/**
			*  Returns whether or not this object has been marked as
			deleted by the Pixel::SceneManager.
			*  If this returns true, you should not be interacting with
			this object anymore, or you could come across undefined behavior.
			*/
			bool IsDeleted();

			/**
			*  Returns whether or not this object is of the given type in the template.
			*/
			template<typename T> bool IsA();

		protected:

			friend class Pixel::SceneManager;
			friend class Pixel::GuiService;

			void _invokeEvent(Pixel::Event) const;

			std::string _id;
			std::chrono::time_point<std::chrono::steady_clock> _createdAt;
			std::map<Pixel::EventType, std::vector<Pixel::EventCallbackId>> _connectedEvents;
			bool _isDeleted;
			std::string _name;

	};

	template<typename T>
	bool Object::IsA()
	{
		return dynamic_cast<T*>(this) != nullptr;
	}

}

#pragma warning(pop)