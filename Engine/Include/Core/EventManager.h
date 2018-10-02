/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Core/EventManager.h
*/

#pragma once

#include "Include/Common.h"

/* Forward declarations */
namespace Pixel::Object
{
	class Object;
	class PhysicalObject;
}

#pragma warning(push)
#pragma warning(disable: 4251)

namespace Pixel {

	/**
	*  A unique ID binded to a specific event callback in the EventManager.
	*/
	typedef std::string EventCallbackId;

	/**
	*  The Pixel::EventType enum contains all the different types of events
	that functions can be binded to.
	*  Not all objects and services will use these events, read the documentation
	for the specific EventType for details about the event and how it works.
	*/
	enum class EventType
	{
		/**
		*  A generic event that doesn't represent anything in specific.
		*  No objects or services in PixelEngine currently invoke this event.
		*  You can create your own events using this EventType.
		*/
		GenericEvent,

		/**
		*  This event is invoked when a solid object collides with another solid object.
		*  Objects that can invoke this event:
		- Object::PhysicalObject (and derived objects)
		*/
		CollisionEvent,

		/**
		*  This event is invoked when an object intersects into another object.
		For this to happen, one or both of the objects have to be non-solid.
		*  Objects that can invoke this event:
		- Object::PhysicalObject (and derived objects)
		*/
		IntersectionEvent
	};

	/**
	*  The Pixel::Event struct is used to relay event information to binded
	event callback functions.
	*  Not all properties of this struct will be filled out, it depends on
	what type of event the struct is representing.
	*/
	struct PIXEL_API Event
	{
		Pixel::EventType type; //* The type of event that was invoked.
		std::chrono::time_point<std::chrono::steady_clock> invokedAt; //* The time point that the event was invoked at.
		Pixel::EventCallbackId invoker; //* The event callback that invoked this specific event.

		/**
		*  The object the event was binded to.
		*  This property is only applicable if the event was binded to a game object.
		*/
		std::weak_ptr<Pixel::Object::Object> object;

		/**
		*  The object that the binded object collided with.
		*  This property is only applicable to:
		- EventType::CollisionEvent
		- EventType::IntersectionEvent
		*/
		std::weak_ptr<Pixel::Object::PhysicalObject> collidedObject;
	};

	/**
	*  The function prototype for all binded event callback functions.
	*/
	typedef void EventCallback(const Pixel::Event);

	/**
	*  The Pixel::EventManager is a singleton service used to bind
	and invoke event callback functions.

	*  Most game objects and services In Pixel Engine use this service
	to implement an event system for themselves.

	*  This service should only really be used when making your own event systems.
	*/
	class PIXEL_API EventManager final
	{

		PIXEL_DEFINE_SINGLETON(Pixel::EventManager);

		public:

			/**
			*  Class constructor
			*/
			EventManager();

			/**
			*  Class deconstructor
			*/
			~EventManager();

			/**
			*  Registers an event callback function to the EventManager
			and returns a unique id representing the binded function.
			*/
			Pixel::EventCallbackId RegisterCallback(Pixel::EventCallback*);

			/**
			*  Unregisters an event callback function from the EventManager
			given its unique event callback ID.
			*/
			void UnregisterCallback(Pixel::EventCallbackId);

			/**
			*  Invokes the specified event callback function given its
			unique event callback ID and passes the given Pixel::Event
			to the callback function.
			*/
			void InvokeCallback(Pixel::EventCallbackId, Pixel::Event) const;

			/**
			*  Invokes the specified event callback function given its
			unique event callback ID and passes a generic Pixel::Event
			to the callback function.
			*/
			void InvokeCallback(Pixel::EventCallbackId) const;

		private:

			std::map<Pixel::EventCallbackId, Pixel::EventCallback*> _connectedCallbacks;

	};
	
}

#pragma warning(pop)