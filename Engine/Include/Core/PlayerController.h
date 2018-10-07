/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Core/PlayerController.h
*/

#pragma once

#include "Include/Common.h"

#include "Include/Core/UserInputService.h"
#include "Include/Object/PhysicalObject.h"

#pragma warning(push)
#pragma warning(disable: 4251)

namespace Pixel {

	/**
	*  TODO
	*/
	class PIXEL_API PlayerController final
	{

		PIXEL_DEFINE_SINGLETON(Pixel::PlayerController);

		public:

			/**
			*  Class constructor
			*/
			PlayerController();

			/**
			*  Class deconstructor
			*/
			~PlayerController();

			/**
			*  TODO
			*/
			void Update();

			/**
			*  TODO
			*/
			void ControlObject(std::weak_ptr<Pixel::Object::PhysicalObject>);

			/**
			*  TODO
			*/
			void UncontrolObject();

			/**
			*  TODO
			*/
			void SetMoveSpeed(double);

			/**
			*  TODO
			*/
			void SetControlsEnabled(bool);

			/**
			*  TODO
			*/
			void SetMoveKeyLeft(Pixel::Key);

			/**
			*  TODO
			*/
			void SetMoveKeyRight(Pixel::Key);

			/**
			*  TODO
			*/
			void SetMoveKeyUp(Pixel::Key);

			/**
			*  TODO
			*/
			void SetMoveKeyDown(Pixel::Key);

			/**
			*  TODO
			*/
			std::shared_ptr<Pixel::Object::PhysicalObject> GetControlledObject() const;

			/**
			*  TODO
			*/
			bool IsControlling() const;

			/**
			*  TODO
			*/
			double GetMoveSpeed() const;

			/**
			*  TODO
			*/
			bool IsControlsEnabled() const;

			/**
			*  TODO
			*/
			Pixel::Key GetMoveKeyLeft() const;

			/**
			*  TODO
			*/
			Pixel::Key GetMoveKeyRight() const;

			/**
			*  TODO
			*/
			Pixel::Key GetMoveKeyUp() const;

			/**
			*  TODO
			*/
			Pixel::Key GetMoveKeyDown() const;

		private:

			bool _hasControlledObject;
			std::weak_ptr<Pixel::Object::PhysicalObject> _controlledObject;
			double _moveSpeed;
			bool _controlsEnabled;

			Pixel::Key _moveKeyLeft;
			Pixel::Key _moveKeyRight;
			Pixel::Key _moveKeyUp;
			Pixel::Key _moveKeyDown;

	};

}

#pragma warning(pop)