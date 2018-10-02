/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Source/Core/EventManager.cpp
*/

#include "Include/Core/EventManager.h"

#include "Include/PixelError.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>

PIXEL_DECLARE_SINGLETON(Pixel::EventManager);

Pixel::EventManager::EventManager()
{
	PIXEL_SINGLETON_CONSTRUCTOR(Pixel::EventManager);
}

Pixel::EventManager::~EventManager()
{
	PIXEL_SINGLETON_DECONSTRUCTOR(Pixel::EventManager);
}

Pixel::EventCallbackId Pixel::EventManager::RegisterCallback(Pixel::EventCallback* callback)
{
	Pixel::EventCallbackId callbackId = (Pixel::EventCallbackId)boost::lexical_cast<std::string>(boost::uuids::random_generator()());
	_connectedCallbacks[callbackId] = callback;
	Pixel::StandardOut::Singleton()->Printf(Pixel::OutputType::Info, "EventManager::RegisterCallback() - %s", callbackId.c_str());
	return callbackId;
}

void Pixel::EventManager::UnregisterCallback(Pixel::EventCallbackId callbackId)
{
	if (_connectedCallbacks.find(callbackId) != _connectedCallbacks.end())
	{
		_connectedCallbacks.erase(callbackId);
		Pixel::StandardOut::Singleton()->Printf(Pixel::OutputType::Info, "EventManager::UnregisterCallback() - %s", callbackId.c_str());
	}
	else
	{
		PixelError("EventManager::UnregisterCallback() - No event callback connected with id \"" + callbackId + "\"");
		return;
	}
}

void Pixel::EventManager::InvokeCallback(Pixel::EventCallbackId callbackId, Pixel::Event e) const
{
	auto callback = _connectedCallbacks.find(callbackId);
	if (callback != _connectedCallbacks.end())
	{
		//Pixel::StandardOut::Singleton()->Printf(Pixel::OutputType::Info, "EventManager::InvokeCallback() - %s", callbackId.c_str());
		e.invoker = callbackId;
		e.invokedAt = std::chrono::high_resolution_clock::now();
		callback->second(e);
	}
	else
	{
		PixelError("EventManager::InvokeCallback() - No event callback connected with id \"" + callbackId + "\"");
		return;
	}
}

void Pixel::EventManager::InvokeCallback(Pixel::EventCallbackId callbackId) const
{
	Pixel::Event e = Pixel::Event();
	e.type = Pixel::EventType::GenericEvent;
	e.invoker = callbackId;
	e.invokedAt = std::chrono::high_resolution_clock::now();
	InvokeCallback(callbackId, e);
}