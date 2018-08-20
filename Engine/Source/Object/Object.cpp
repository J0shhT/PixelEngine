#include "Include/Object/Object.h"

#include "Include/PixelOutput.h"

PIXEL_DECLARE_OBJECT(Object);

Pixel::Object::Object::Object()
{
	PIXEL_OBJECT_CONSTRUCTOR(Object);
	std::ostringstream strStream;
	strStream << "Object::Object() - Created " << this;
	Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Debug, strStream.str().c_str());
}

Pixel::Object::Object::~Object()
{
	std::ostringstream strStream;
	strStream << "Object::Object() - Destroyed " << this;
	Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Debug, strStream.str().c_str());
	PIXEL_OBJECT_DECONSTRUCTOR(Object);
}

std::string Pixel::Object::Object::GetId() const
{
	return _id;
}

Pixel::EventCallbackId Pixel::Object::Object::Bind(Pixel::EventType type, Pixel::EventCallback* callback)
{
	Pixel::EventCallbackId callbackId = Pixel::EventManager::Singleton()->RegisterCallback(callback);
	if (_connectedEvents.find(type) == _connectedEvents.end())
	{
		_connectedEvents[type] = std::vector<Pixel::EventCallbackId>();
	}
	_connectedEvents[type].push_back(callbackId);
	return callbackId;
}

void Pixel::Object::Object::Unbind(Pixel::EventType type, Pixel::EventCallbackId callbackId)
{
	Pixel::EventManager::Singleton()->UnregisterCallback(callbackId);
	if (_connectedEvents.find(type) != _connectedEvents.end())
	{
		for (auto iter = _connectedEvents[type].begin(); iter != _connectedEvents[type].end();)
		{
			if (*iter == callbackId)
			{
				iter = _connectedEvents[type].erase(iter);
				return;
			}
			else
			{
				iter++;
			}
		}
	}
}

double Pixel::Object::Object::GetAge() const
{
	std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::high_resolution_clock::now();
	return static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(now - _createdAt).count()) / 1000000.0;
}

std::string Pixel::Object::Object::GetName() const
{
	return _name;
}

void Pixel::Object::Object::SetName(const std::string &name)
{
	_name = name;
}

bool Pixel::Object::Object::IsDeleted()
{
	return _isDeleted;
}

void Pixel::Object::Object::_invokeEvent(Pixel::Event::Event e) const
{
	if (_connectedEvents.find(e.type) != _connectedEvents.end())
	{
		for (auto iter = _connectedEvents.at(e.type).begin(); iter != _connectedEvents.at(e.type).end();)
		{
			size_t sizeBefore = _connectedEvents.at(e.type).size();
			Pixel::EventManager::Singleton()->InvokeCallback(*iter, e);
			if (_connectedEvents.at(e.type).size() > 0)
			{
				if (sizeBefore == _connectedEvents.at(e.type).size())
				{
					iter++;
				}
			}
			else
			{
				break;
			}
		}
	}
}
