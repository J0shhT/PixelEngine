#pragma once

#include "Include/Common.h"

#include "Object.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace Pixel::Object {

	/**
	*  TODO
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
			*  TODO
			*/
			virtual void Render() = 0;

		protected:

			GLuint _vertexBufferId;
			GLuint _colorBufferId;
			GLuint _textureBufferId;

	};

}