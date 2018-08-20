#pragma once

#include "Include/Common.h"

namespace Pixel::Object
{
	class Object;
	class PhysicalObject;
}

namespace Pixel {

	typedef std::string EventCallbackId;

	/**
	*  TODO
	*/
	enum class EventType
	{
		/**
		*  A generic event that doesn't represent
		anything in specific.
		*/
		GenericEvent,

		/**
		*  This event is invoked when a solid object
		collides with another solid object.
		*/
		CollisionEvent,

		/**
		*  This event is invoked when an object intersects
		into another object. For this to happen, one or both
		of the objects have to be non-solid.
		*/
		IntersectionEvent
	};

	namespace Event {

		/**
		*  TODO
		*/
		struct PIXEL_API Event
		{
			Pixel::EventType type;
			std::chrono::time_point<std::chrono::steady_clock> invokedAt;
			Pixel::EventCallbackId invoker;

			std::weak_ptr<Pixel::Object::Object> object;
			std::weak_ptr<Pixel::Object::PhysicalObject> collidedObject;
		};

	}

	typedef void EventCallback(const Pixel::Event::Event);

	/**
	*  TODO
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
			*  TODO
			*/
			Pixel::EventCallbackId RegisterCallback(Pixel::EventCallback*);

			/**
			*  TODO
			*/
			void UnregisterCallback(Pixel::EventCallbackId);

			/**
			*  TODO
			*/
			void InvokeCallback(Pixel::EventCallbackId, Pixel::Event::Event) const;

			/**
			*  TODO
			*/
			void InvokeCallback(Pixel::EventCallbackId) const;

		private:

			std::map<Pixel::EventCallbackId, Pixel::EventCallback*> _connectedCallbacks;

	};
	
}