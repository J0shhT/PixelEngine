#pragma once

/* Standard Libraries */
#include "Common.h"

/* Core */
#include "Include/PixelOutput.h"
#include "Include/PixelError.h"
#include "Include/Core/PixelApp.h"
#include "Include/Core/SceneManager.h"
#include "Include/Core/SelectionService.h"
#include "Include/Core/UserInputService.h"
#include "Include/Core/ContentProvider.h"
#include "Include/Core/SoundService.h"

/* Graphics */
#include "Include/Graphics/RenderService.h"
#include "Include/Graphics/Shader.h"

/* Physics */
#include "Include/Physics/PhysicsService.h"

/* Network */
#include "Include/Network/HttpService.h"

/* Object */
#include "Include/Object/Object.h"
#include "Include/Object/RenderableObject.h"
#include "Include/Object/PhysicalObject.h"
#include "Include/Object/Rectangle.h"
#include "Include/Object/Camera.h"

/* Type */
#include "Include/Type/Position.h"
#include "Include/Type/Size.h"
#include "Include/Type/WorldPosition.h"
#include "Include/Type/Velocity.h"
#include "Include/Type/Color.h"

/* Entry point macro */
#define PixelMain(func) \
	int main() { \
		try \
		{ \
			func ## (); \
		} \
		catch (Pixel::Exception::FatalError e) \
		{ \
			Pixel::LogService::Singleton()->UploadLogs(Pixel::LogType::CrashLog); \
			return 1; \
		} \
		return 0; \
	}

/* Helper macros */

/**
*  Argument 1: The object classname to create that is inside the namespace Pixel::Object
*  Returns a shared_ptr to the object created
*/
#define PixelCreateObject(type) Pixel::SceneManager::Singleton()->CreateObject<Pixel::Object:: ## type>();

/**
*  Argument 1: shared_ptr to a class that inherits from Pixel::Object::Object
*  Removes the specified object from the game scene and marks it as deleted.
*  This macro also frees the ownership of the shared_ptr given to the macro.
*/
#define PixelDeleteObject(obj) if (Pixel::SceneManager::Singleton()->DeleteObject(obj)) { obj.reset(); }