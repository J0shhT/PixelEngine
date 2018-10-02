/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Source/Object/Camera.cpp
*/

#include "Include/Object/Camera.h"

#include "Include/PixelOutput.h"
#include "Include/PixelError.h"

#include "Include/Core/UserInputService.h"

PIXEL_DECLARE_OBJECT(Camera);

Pixel::Object::Camera::Camera() : _position(Pixel::Type::WorldPosition(0.0)), _cameraType(Pixel::CameraType::Scriptable), _speed(300.0)
{
	PIXEL_OBJECT_CONSTRUCTOR(Camera);
}

Pixel::Object::Camera::~Camera()
{
	PIXEL_OBJECT_DECONSTRUCTOR(Camera);
}

Pixel::CameraType Pixel::Object::Camera::GetCameraType() const
{
	return _cameraType;
}

Pixel::Type::WorldPosition Pixel::Object::Camera::GetPosition() const
{
	if (_cameraType == Pixel::CameraType::Attach)
	{
		if (Pixel::Util::IsWeakPtrInitialized<Pixel::Object::PhysicalObject>(_target))
		{
			return GetTarget()->GetPosition();
		}
	}
	return _position;
}

double Pixel::Object::Camera::GetFreeCameraSpeed() const
{
	return _speed;
}

std::shared_ptr<Pixel::Object::PhysicalObject> Pixel::Object::Camera::GetTarget() const
{
	return _target.lock();
}

void Pixel::Object::Camera::SetCameraType(Pixel::CameraType type)
{
	_cameraType = type;
}

void Pixel::Object::Camera::SetPosition(Pixel::Type::WorldPosition position)
{
	if (_cameraType == Pixel::CameraType::Attach)
	{
		PixelWarning("Camera::SetPosition() - CameraType is set to Attach and cannot be manually positioned");
		return;
	}
	_position = position;
}

void Pixel::Object::Camera::SetFreeCameraSpeed(double value)
{
	_speed = value;
}

void Pixel::Object::Camera::SetTarget(std::shared_ptr<Pixel::Object::PhysicalObject> object)
{
	_target = object;
}

void Pixel::Object::Camera::Update(double frameDelta)
{
	static Pixel::UserInputService* userInputService = Pixel::UserInputService::Singleton();

	if (GetCameraType() == Pixel::CameraType::Scriptable)
	{
		return;
	}
	else if (GetCameraType() == Pixel::CameraType::FreeCamera)
	{
		if (_speed != 0.0)
		{
			char movementDirectionX = 0;
			char movementDirectionY = 0;

			if (userInputService->IsKeyDown(Pixel::Key::KeyW))
				movementDirectionY = -1;
			if (userInputService->IsKeyDown(Pixel::Key::KeyS))
				movementDirectionY = 1;
			if (userInputService->IsKeyDown(Pixel::Key::KeyD))
				movementDirectionX = 1;
			if (userInputService->IsKeyDown(Pixel::Key::KeyA))
				movementDirectionX = -1;

			Pixel::Type::WorldPosition cameraPosition = GetPosition();
			SetPosition(Pixel::Type::WorldPosition(
				cameraPosition.GetX() + (_speed * movementDirectionX * frameDelta),
				cameraPosition.GetY() + (_speed * movementDirectionY * frameDelta)
			));
		}
	}
	else if (GetCameraType() == Pixel::CameraType::Attach)
	{
		if (Pixel::Util::IsWeakPtrInitialized<Pixel::Object::PhysicalObject>(_target)) {
			SetPosition(GetTarget()->GetPosition());
		}
	}
}