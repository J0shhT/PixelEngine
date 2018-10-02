/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Physics/PhysicsService.h
*/

#pragma once

#include "Include/Common.h"

namespace Pixel {

	/**
	*  The Pixel::PhysicsService is a singleton service which handles
	all high-level physics calls in Pixel Engine. This service is responsible
	for going through all physical objects and calling their physics step functions.
	*/
	class PIXEL_API PhysicsService final
	{

		PIXEL_DEFINE_SINGLETON(Pixel::PhysicsService);

		public:

			/**
			*  Class constructor
			*/
			PhysicsService();

			/**
			*  Class deconstructor
			*/
			~PhysicsService();

			/**
			*  Calculates the frame delta value that should be
			used for the next physics frame simulation.
			*  See PhysicsService::GetLastPhysicsFrameDelta().
			*/
			void TimeFrame();

			/**
			*  Simulates the physics of all game world objects.
			*/
			void SimulateWorldObjects();

			/**
			*  Simulates the physics of all world objects created by Pixel Engine.
			*/
			void SimulateSystemObjects();

			/**
			*  Returns the last calculated frame delta for PhysicsService.
			*  Frame delta is used to accurately simulate physics even with
			varrying FPS or screen refresh rate.
			*  Frame delta is equal to the time between two calls to TimeFrame().
			*/
			double GetLastPhysicsFrameDelta() const;

		private:

			double _lastFrameDelta = 0.0;

	};

}