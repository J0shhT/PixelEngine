/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Object/RenderableObject.h
*/

#pragma once

#include "Include/Common.h"

#include "Object.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace Pixel::Object {

	/**
	*  The Object::RenderableObject object is the base object
	class for all objects that can be rendered in some way
	in Pixel Engine.

	*  This includes physical objects and gui objects.

	*  All objects that can be rendered inherit from this class.
	*/
	class PIXEL_API RenderableObject : public Object
	{

		PIXEL_DEFINE_OBJECT(RenderableObject);

		public:

			/**
			*  Class constructor
			*/
			RenderableObject();

			/**
			*  Class deconstructor
			*/
			virtual ~RenderableObject();

			/**
			*  Abstract function to render one frame of this object.
			*/
			virtual void Render() = 0;

		protected:

			GLuint _vertexBufferId;
			GLuint _colorBufferId;
			GLuint _textureBufferId;

	};

}