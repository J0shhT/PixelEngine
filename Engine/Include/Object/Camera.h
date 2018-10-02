/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Object/Camera.h
*/

#pragma once

#include "Include/Common.h"

#include "PhysicalObject.h"
#include "Include/Type/WorldPosition.h"

namespace Pixel {

	/**
	*  The Pixel::CameraType enum contains all the different
	camera types supported by the Object::Camera.
	*/
	enum class CameraType
	{
		Scriptable, //* Camera will not be updated automatically by the engine
		FreeCamera, //* Camera can be moved via WASD controls
		Attach //* Camera will follow the target object
	};

}

#pragma warning(push)
#pragma warning(disable: 4251)

namespace Pixel::Object {

	/**
	*  The Object::Camera is used to represent the current
	view by the user in the game.
	*  Supports different camera modes.
	*  Use CameraType::Scriptable to manually control the 
	camera yourself in your code.
	*  Use CameraType::FreeCamera to allow the engine to
	automatically move the camera based on WASD controls.
	*  Use CameraType::Attach to make the camera follow
	an object already in the game.
	*/
	class PIXEL_API Camera : public Object
	{

		PIXEL_DEFINE_OBJECT(Camera);

		public:

			/**
			*  Class constructor
			*/
			Camera();

			/**
			*  Class deconstructor
			*/
			virtual ~Camera();

			/**
			*  Returns the current camera type being used.
			*/
			Pixel::CameraType GetCameraType() const;

			/**
			*  Returns the current world position of the camera.
			*  If CameraType::Attach is being used, will return
			the position of the attached object instead.
			*/
			Pixel::Type::WorldPosition GetPosition() const;

			/**
			*  Returns the speed of the free camera.
			*/
			double GetFreeCameraSpeed() const;

			/**
			*  Returns the current target of the camera for CameraType::Attach.
			*/
			std::shared_ptr<Pixel::Object::PhysicalObject> GetTarget() const;

			/**
			*  Sets the camera type to be used.
			*  See Pixel::CameraType enum.
			*/
			void SetCameraType(Pixel::CameraType);

			/**
			*  Sets the position of the camera.
			*  See Pixel::CameraType::Scriptable enum.
			*/
			void SetPosition(Pixel::Type::WorldPosition);

			/**
			*  Sets the speed of the free camera
			*  See Pixel::CameraType::FreeCamera enum.
			*/
			void SetFreeCameraSpeed(double);

			/**
			*  Sets the target of the camera.
			*  See Pixel::CameraType::Attach enum.
			*/
			void SetTarget(std::shared_ptr<Pixel::Object::PhysicalObject>);

			/**
			*  Updates the camera's position if set to CameraType::Attach
			*  Sets the camera's position if set to CameraType::FreeCamera
			*  This does nothing if CameraType::Scriptable is set.
			*/
			void Update(double frameDelta);

		protected:

			Pixel::CameraType _cameraType;
			Pixel::Type::WorldPosition _position;
			double _speed;
			std::weak_ptr<Pixel::Object::PhysicalObject> _target;

	};

}

#pragma warning(pop)