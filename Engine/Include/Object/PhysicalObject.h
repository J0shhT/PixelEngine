/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Object/PhysicalObject.h
*/

#pragma once

#include "Include/Common.h"

#include "RenderableObject.h"

#include "Include/Core/ContentProvider.h"

#include "Include/Type/WorldPosition.h"
#include "Include/Type/Size.h"
#include "Include/Type/Velocity.h"
#include "Include/Type/Color.h"

#pragma warning(push)
#pragma warning(disable: 4251)

namespace Pixel::Object {

	/**
	*  The Object::PhysicalObject game object is the base object
	class for all game objects that have a physical aspect to them,
	have a physical existance in the game world, and interact with 
	other physical objects dynamically.

	*  All physical objects have a position in the world, size, color,
	velocity, and optionally, a texture.

	*  When a physical object is anchored via SetAnchored(), the object 
	will no longer physically move from its own velocity. An object that 
	is anchored can still be moved manually via SetPosition().

	*  When a physical object is set to not be solid via SetSolid(), the
	object will no longer collide with other physical objects, and other
	physical objects will not collide with it.
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
			*  Returns the world position of this object.
			*/
			Pixel::Type::WorldPosition GetPosition() const;

			/**
			*  Returns the size of this object (in world coordinates).
			*/
			Pixel::Type::Size GetSize() const;

			/**
			*  Returns the velocity of this object (in world space).
			*/
			Pixel::Type::Velocity GetVelocity() const;

			/**
			*  Returns whether or not this object is anchored.
			*  Objects that are anchored will no longer move from its own velocity.
			*/
			bool IsAnchored() const;

			/**
			*  Returns whether or not this object is solid.
			*  Objects that are not solid will not collide with other objects.
			*/
			bool IsSolid() const;

			/**
			*  Returns the color of this object.
			*/
			Pixel::Type::Color GetColor() const;

			/**
			*  Returns the file path of the texture of this object.
			*  Returns an empty string if the object has no texture.
			*/
			std::string GetTexture() const;

			/**
			*  Sets the world position of this object.
			*/
			void SetPosition(Pixel::Type::WorldPosition);

			/**
			*  Sets the size of this object (in world coordinates).
			*/
			void SetSize(Pixel::Type::Size);

			/**
			*  Sets the velocity of this object (in world space).
			*/
			void SetVelocity(Pixel::Type::Velocity);

			/**
			*  Sets whether or not this object is anchored.
			*  Objects that are anchored will no longer move from its own velocity.
			*/
			void SetAnchored(bool);

			/**
			*  Sets whether or not this object is solid.
			*  Objects that are not solid will not collide with other objects.
			*/
			void SetSolid(bool);

			/**
			*  Sets the color of this object.
			*/
			void SetColor(Pixel::Type::Color);

			/**
			*  Sets the texture of this object from the given file path.
			*  See Pixel::ContentProvider documentation for supported image files.
			*/
			void SetTexture(std::string filePath);

			/**
			*  Abstract function to step through one physics frame for this object.
			*/
			virtual void StepPhysics(double frameDelta) = 0;

		protected:

			virtual void _checkCollisions() = 0;

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

	};

}

#pragma warning(pop)