#pragma once

#include "Include/Common.h"

#include "Include/Type/WorldPosition.h"

#include "PhysicalObject.h"

namespace Pixel
{
	enum class CameraType
	{
		Scriptable,
		FreeCamera,
		Attach
	};
}

namespace Pixel::Object {

	/**
	*  TODO
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
			*  TODO
			*/
			Pixel::CameraType GetCameraType() const;

			/**
			*  TODO
			*/
			Pixel::Type::WorldPosition GetPosition() const;

			/**
			*  TODO
			*/
			double GetFreeCameraSpeed() const;

			/**
			*  TODO
			*/
			std::shared_ptr<Pixel::Object::PhysicalObject> GetTarget() const;

			/**
			*  TODO
			*/
			void SetCameraType(Pixel::CameraType);

			/**
			*  TODO
			*/
			void SetPosition(Pixel::Type::WorldPosition);

			/**
			*  TODO
			*/
			void SetFreeCameraSpeed(double);

			/**
			*  TODO
			*/
			void SetTarget(std::shared_ptr<Pixel::Object::PhysicalObject>);

			/**
			*  TODO
			*/
			void Update(double frameDelta);

		protected:

			Pixel::CameraType _cameraType;
			Pixel::Type::WorldPosition _position;
			double _speed;
			std::weak_ptr<Pixel::Object::PhysicalObject> _target;


	};

}