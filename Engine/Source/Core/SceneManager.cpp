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

std::shared_ptr<Pixel::Object::Object> Pixel::SceneManager::GetObjectById(const std::string &id)
{
	if (_objects.count(id) > 0)
	{
		return _objects.at(id);
	}
	return nullptr;
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
