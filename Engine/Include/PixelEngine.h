/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Alpha 1.0.0.0 (September 30th, 2018)

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/PixelEngine.h
*/

#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE

/* Standard Libraries */
#include "Common.h"

/* Core */
#include "Include/PixelOutput.h"
#include "Include/PixelError.h"
#include "Include/Core/ContentProvider.h"
#include "Include/Core/EventManager.h"
#include "Include/Core/LogService.h"
#include "Include/Core/PixelApp.h"
#include "Include/Core/SceneManager.h"
#include "Include/Core/SelectionService.h"
#include "Include/Core/SoundService.h"
#include "Include/Core/UserInputService.h"

/* Graphics */
#include "Include/Graphics/GuiService.h"
#include "Include/Graphics/RenderService.h"
#include "Include/Graphics/Shader.h"

/* Network */
#include "Include/Network/HttpService.h"

/* Base Objects */
#include "Include/Object/Object.h"
#include "Include/Object/RenderableObject.h"
#include "Include/Object/PhysicalObject.h"
#include "Include/Object/GuiObject.h"

/* Misc Objects */
#include "Include/Object/Camera.h"

/* Renderable Game Objects */
#include "Include/Object/Rectangle.h"

/* GUI Objects */
#include "Include/Object/BasicTextGui.h"

/* Physics */
#include "Include/Physics/PhysicsService.h"

/* Type */
#include "Include/Type/Position.h"
#include "Include/Type/Size.h"
#include "Include/Type/WorldPosition.h"
#include "Include/Type/Velocity.h"
#include "Include/Type/Color.h"

/* Entry point macro */
#ifdef _CONSOLE
	#define PixelMain(func) \
		int main() { \
			try \
			{ \
				Pixel::ValidateEngineVersion(PIXEL_ENGINE_VERSION_INTERNAL); \
				func ## (); \
			} \
			catch (Pixel::Exception::FatalError e) \
			{ \
				Pixel::LogService::Singleton()->UploadLogs(Pixel::LogType::CrashLog); \
				return 1; \
			} \
			return 0; \
		}
#else
	#ifdef _WINDOWS
		#define PixelMain(func) \
			int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) { \
				try \
				{ \
					Pixel::ValidateEngineVersion(PIXEL_ENGINE_VERSION_INTERNAL); \
					func ## (); \
				} \
				catch (Pixel::Exception::FatalError e) \
				{ \
					Pixel::LogService::Singleton()->UploadLogs(Pixel::LogType::CrashLog); \
					return 1; \
				} \
				return 0; \
			}
	#else
		#error "You must either define _WINDOWS or _CONSOLE in your preprocessor definitions depending on which subsystem you are using!"
	#endif
#endif