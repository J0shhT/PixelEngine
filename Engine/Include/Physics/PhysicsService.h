#pragma once

#include "Include/Common.h"

namespace Pixel {

	/**
	*  TODO
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
			*  TODO
			*/
			void TimeFrame();

			/**
			*  TODO
			*/
			void SimulateGameObjects();

			/**
			*  TODO
			*/
			void SimulateSystemObjects();

			/**
			*  TODO
			*/
			double GetLastPhysicsFrameDelta() const;

		private:

			double _lastFrameDelta = 0.0;
	};

}