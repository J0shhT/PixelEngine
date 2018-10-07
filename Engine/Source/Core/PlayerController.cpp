/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Source/Core/PlayerController.cpp
*/

#include "Include/Core/PlayerController.h"

#include "Include/PixelError.h"

PIXEL_DECLARE_SINGLETON(Pixel::PlayerController);

Pixel::PlayerController::PlayerController()
{
	PIXEL_SINGLETON_CONSTRUCTOR(Pixel::PlayerController);
	_controlsEnabled = true;
	_moveKeyLeft = Pixel::Key::KeyA;
	_moveKeyRight = Pixel::Key::KeyD;
	_moveKeyUp = Pixel::Key::KeyW;
	_moveKeyDown = Pixel::Key::KeyS;
	_moveSpeed = 50.0;
}

Pixel::PlayerController::~PlayerController()
{
	PIXEL_SINGLETON_DECONSTRUCTOR(Pixel::PlayerController);
}

void Pixel::PlayerController::Update()
{
	static auto userInputService = Pixel::UserInputService::Singleton();
	
	if (!IsControlling() || GetMoveSpeed() == 0.0)
		return;

	auto object = GetControlledObject();
	Pixel::Type::Velocity moveVelocity = PixelVelocity();

	if (userInputService->IsKeyDown(GetMoveKeyLeft()) && !userInputService->IsKeyDown(GetMoveKeyRight()))
		moveVelocity.SetX(-GetMoveSpeed());
	if (userInputService->IsKeyDown(GetMoveKeyRight()) && !userInputService->IsKeyDown(GetMoveKeyLeft()))
		moveVelocity.SetX(GetMoveSpeed());
	if (userInputService->IsKeyDown(GetMoveKeyUp()) && !userInputService->IsKeyDown(GetMoveKeyDown()))
		moveVelocity.SetY(GetMoveSpeed());
	if (userInputService->IsKeyDown(GetMoveKeyDown()) && !userInputService->IsKeyDown(GetMoveKeyUp()))
		moveVelocity.SetY(-GetMoveSpeed());

	object->SetVelocity(moveVelocity);
}

void Pixel::PlayerController::ControlObject(std::weak_ptr<Pixel::Object::PhysicalObject> object)
{
	_controlledObject = object;
	_hasControlledObject = true;
}

void Pixel::PlayerController::UncontrolObject()
{
	_hasControlledObject = false;
}

void Pixel::PlayerController::SetMoveSpeed(double value)
{
	_moveSpeed = value;
}

void Pixel::PlayerController::SetControlsEnabled(bool value)
{
	_controlsEnabled = value;
}

void Pixel::PlayerController::SetMoveKeyLeft(Pixel::Key key)
{
	_moveKeyLeft = key;
}

void Pixel::PlayerController::SetMoveKeyRight(Pixel::Key key)
{
	_moveKeyRight = key;
}

void Pixel::PlayerController::SetMoveKeyUp(Pixel::Key key)
{
	_moveKeyUp = key;
}

void Pixel::PlayerController::SetMoveKeyDown(Pixel::Key key)
{
	_moveKeyDown = key;
}

std::shared_ptr<Pixel::Object::PhysicalObject> Pixel::PlayerController::GetControlledObject() const
{
	if (!IsControlling())
		return nullptr;

	return _controlledObject.lock();
}

bool Pixel::PlayerController::IsControlling() const
{
	return _hasControlledObject 
		&& Pixel::Util::IsWeakPtrInitialized<Pixel::Object::PhysicalObject>(_controlledObject);
}

double Pixel::PlayerController::GetMoveSpeed() const
{
	return _moveSpeed;
}

bool Pixel::PlayerController::IsControlsEnabled() const
{
	return _controlsEnabled;
}

Pixel::Key Pixel::PlayerController::GetMoveKeyLeft() const
{
	return _moveKeyLeft;
}

Pixel::Key Pixel::PlayerController::GetMoveKeyRight() const
{
	return _moveKeyRight;
}

Pixel::Key Pixel::PlayerController::GetMoveKeyUp() const
{
	return _moveKeyUp;
}

Pixel::Key Pixel::PlayerController::GetMoveKeyDown() const
{
	return _moveKeyDown;
}

