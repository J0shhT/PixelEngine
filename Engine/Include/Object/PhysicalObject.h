#pragma once

#include "Include/Common.h"

#include "RenderableObject.h"

#include "Include/Type/WorldPosition.h"
#include "Include/Type/Size.h"
#include "Include/Type/Velocity.h"
#include "Include/Type/Color.h"

#include "Include/Core/ContentProvider.h"

namespace Pixel::Object {

	/**
	*  TODO
	*/
	class PIXEL_API PhysicalObject : public RenderableObject
	{

		PIXEL_DEFINE_OBJECT(PhysicalObject);

		public:

			/**
			*  Class constructor
			*/
			PhysicalObject();

			/**
			*  Class deconstructor
			*/
			virtual ~PhysicalObject();

			/**
			*  TODO
			*/
			Pixel::Type::WorldPosition GetPosition() const;

			/**
			*  TODO
			*/
			Pixel::Type::Size GetSize() const;

			/**
			*  TODO
			*/
			Pixel::Type::Velocity GetVelocity() const;

			/**
			*  TODO
			*/
			bool IsAnchored() const;

			/**
			*  TODO
			*/
			bool IsSolid() const;

			/**
			*  TODO
			*/
			Pixel::Type::Color GetColor() const;

			/**
			*  TODO
			*/
			std::string GetTexture() const;

			/**
			*  TODO
			*/
			void SetPosition(Pixel::Type::WorldPosition);

			/**
			*  TODO
			*/
			void SetSize(Pixel::Type::Size);

			/**
			*  TODO
			*/
			void SetVelocity(Pixel::Type::Velocity);

			/**
			*  TODO
			*/
			void SetAnchored(bool);

			/**
			*  TODO
			*/
			void SetSolid(bool);

			/**
			*  TODO
			*/
			void SetColor(Pixel::Type::Color);

			/**
			*  TODO
			*/
			void SetTexture(std::string filePath);

			/**
			*  TODO
			*/
			virtual void StepPhysics(double frameDelta) = 0;

		protected:

			Pixel::Type::WorldPosition _position;
			Pixel::Type::Size _size;
			Pixel::Type::Velocity _velocity;
			bool _isAnchored;
			bool _isSolid;
			Pixel::Type::Color _color;
			Pixel::ContentId _texture;

			bool _hasCollisionTop;
			bool _hasCollisionBottom;
			bool _hasCollisionLeft;
			bool _hasCollisionRight;

			virtual void _checkCollisions() = 0;

	};

}