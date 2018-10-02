/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Source/Physics/PhysicsService.cpp
*/

#include "Include/Physics/PhysicsService.h"

#include "Include/PixelError.h"
#include "Include/PixelOutput.h"

#include "Include/Object/PhysicalObject.h"

#include "Include/Core/SceneManager.h"

PIXEL_DECLARE_SINGLETON(Pixel::PhysicsService);

Pixel::PhysicsService::PhysicsService()
{
	PIXEL_SINGLETON_CONSTRUCTOR(Pixel::PhysicsService);
}

Pixel::PhysicsService::~PhysicsService()
{
	PIXEL_SINGLETON_DECONSTRUCTOR(Pixel::PhysicsService);
}

void Pixel::PhysicsService::TimeFrame()
{
	using namespace std::chrono;
	static auto frameLast = high_resolution_clock::now();
	auto frameNow = high_resolution_clock::now();
	_lastFrameDelta = static_cast<double>(duration_cast<microseconds>(frameNow - frameLast).count()) / 1000000.0;
	frameLast = high_resolution_clock::now();
}

void Pixel::PhysicsService::SimulateWorldObjects()
{
	auto gameObjects = Pixel::SceneManager::Singleton()->GetObjects();
	for (auto iter = gameObjects.cbegin(); iter != gameObjects.cend(); ++iter)
	{
		std::shared_ptr<Pixel::Object::Object> object = iter->second;
		if (object->IsA<Pixel::Object::PhysicalObject>())
		{
			std::shared_ptr<Pixel::Object::PhysicalObject> physicsObject = std::dynamic_pointer_cast<Pixel::Object::PhysicalObject>(object);
			object.reset();
			if (!physicsObject->IsAnchored())
				physicsObject->StepPhysics(GetLastPhysicsFrameDelta());
			physicsObject.reset();
		}
	}
}

void Pixel::PhysicsService::SimulateSystemObjects()
{
	
}

double Pixel::PhysicsService::GetLastPhysicsFrameDelta() const
{
	return _lastFrameDelta;
}