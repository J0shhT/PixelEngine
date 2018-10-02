/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Source/Core/SceneManager.cpp
*/

#include "Include/Core/SceneManager.h"

#include "Include/PixelError.h"

PIXEL_DECLARE_SINGLETON(Pixel::SceneManager);

Pixel::SceneManager::SceneManager()
{
	PIXEL_SINGLETON_CONSTRUCTOR(Pixel::SceneManager);
}

Pixel::SceneManager::~SceneManager()
{
	auto iter = _objects.begin();
	while (iter != _objects.end())
	{
		iter->second->_isDeleted = true;
		iter = _objects.erase(iter);
	}
	PIXEL_SINGLETON_DECONSTRUCTOR(Pixel::SceneManager);
}

const std::map<std::string, std::shared_ptr<Pixel::Object::Object>>& Pixel::SceneManager::GetObjects() const
{
	return _objects;
}

std::shared_ptr<Pixel::Object::Object> Pixel::SceneManager::GetObjectById(const std::string& id) const
{
	if (_objects.count(id) > 0)
	{
		return _objects.at(id);
	}
	return nullptr;
}

std::shared_ptr<Pixel::Object::Object> Pixel::SceneManager::GetObjectByName(const std::string& name) const
{
	for (auto iter = _objects.cbegin(); iter != _objects.cend(); iter++)
	{
		if (iter->second->GetName() == name)
		{
			return iter->second;
		}
	}
	return nullptr;
}

size_t Pixel::SceneManager::GetObjectCount() const
{
	return _objects.size();
}

bool Pixel::SceneManager::DeleteObject(const std::string& objectId)
{
	if (GetObjectById(objectId) != nullptr)
	{
		auto object = _objects.at(objectId);
		_objects.erase(objectId);
		object->_isDeleted = true;
		object.reset();
		return true;
	}
	return false;
}

bool Pixel::SceneManager::DeleteObject(std::shared_ptr<Pixel::Object::Object> object)
{
	return DeleteObject(object->GetId());
}

void Pixel::SceneManager::_addObject(std::shared_ptr<Pixel::Object::Object> object)
{
	_objects[object->GetId()] = object;
}
