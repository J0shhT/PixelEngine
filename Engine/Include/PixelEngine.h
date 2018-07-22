#pragma once

/* Standard Libraries */
#include "Common.h"

/* Core */
#include "Include/PixelOutput.h"
#include "Include/PixelError.h"
#include "Include/Core/PixelApp.h"
#include "Include/Core/SceneManager.h"
#include "Include/Core/SelectionService.h"

/* Graphics */
#include "Include/Graphics/RenderService.h"
#include "Include/Graphics/Shader.h"

/* Physics */
//todo

/* Sound */
//todo

/* Network */
#include "Include/Network/HttpService.h"

/* Object */
#include "Include/Object/Object.h"
#include "Include/Object/RenderableObject.h"
#include "Include/Object/PhysicalObject.h"

/* Type */
#include "Include/Type/Position.h"
#include "Include/Type/Size.h"
#include "Include/Type/WorldPosition.h"


/* Helper macros */

/**
*  Argument 1: shared_ptr to a class that inherits from Pixel::Object::Object
*  Removes the specified object from the game scene and marks it as deleted.
*  This macro also frees the ownership of the shared_ptr given to the macro.
*/
#define PixelDeleteObject(obj) if (Pixel::SceneManager::Singleton()->DeleteObject(obj)) { obj.reset(); }