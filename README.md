# Pixel Engine ![](https://img.shields.io/badge/type-game--engine-red.svg) ![](https://img.shields.io/badge/language-C++-yellow.svg) ![](https://img.shields.io/badge/platform-windows-orange.svg)

Pixel Engine is an open-source 2D game engine library for C++ and the Windows platform. Pixel Engine also comes with a level editor (coming soon) to create 2D levels that can be loaded by the engine's API. This is one of my first attempts at creating a game engine and this is mostly just a learning experience for me.

## Libraries
Pixel Engine utilizes the following third-party libraries:
- [OpenGL](https://www.opengl.org/) (Open Graphics Library)
- [SDL](https://www.libsdl.org/) (Simple DirectMedia Layer)
- [wxWidgets](https://www.wxwidgets.org/) (wxWidgets GUI Library)
- [FMOD](https://www.fmod.com/) (FMOD Sound System)
- [gainput](https://github.com/jkuhlmann/gainput) (gainput Input Library)
- [libcurl](https://curl.haxx.se/libcurl/) (The Curl Library)
- [RakNet](http://www.jenkinssoftware.com/) (RakNet Networking Middleware)
- [GLUT](https://www.opengl.org/resources/libraries/glut/) (OpenGL Utility Toolkit)
- [GLEW](http://glew.sourceforge.net/) (OpenGL Extension Wrangler)
- [GLM](https://glm.g-truc.net/0.9.8/index.html) (OpenGL Mathematics)
- [SOIL](http://www.lonesock.net/soil.html) (Simple OpenGL Image Library)
- [Boost](http://www.boost.org/) (Boost C++ Libraries)

## Setup for Visual Studio 2017
1. Download the latest available SDK from [here](https://github.com/J0shhT/PixelEngine/releases).
1. Unzip and extract the SDK and place the **PixelEngine** folder in the base directory of your project where your ``.vcxproj`` file is located.
1. Open your project settings and add in order: `$(ProjectDir)PixelEngine`, `$(ProjectDir)PixelEngine\Include`, `$(ProjectDir)PixelEngine\Include\Dependencies`, `$(ProjectDir)PixelEngine\Include\Dependencies\wxWidgets\msvc`, and `$(ProjectDir)PixelEngine\Include\Dependencies\wxWidgets` to your **Additional Include Directories** in **C/C++ > General**
1. Add `$(ProjectDir)PixelEngine` and `$(ProjectDir)PixelEngine\wxWidgets` to your **Additional Library Directories** in **Linker > General**
1. Add `PixelEngine.lib`and `glut32.lib` to your **Additional Dependencies** in **Linker > Input**
1. Change your **C++ Language Standard** to `ISO C++17 Standard` in **C/C++ > Language**
1. Make sure your project is set to unicode mode by setting your **Character Set** to ``Use Unicode Character Set`` in **General** as well as adding `UNICODE` to **Preprocessor Definitions** in **C/C++ > Preprocessor**
1. Compile the code example below. It should build successfully in both release and debug.
1. Add all the contents in **PixelEngine/Bin/** to wherever your built program is running from.

## Code Example
The following code is the most basic Pixel Engine application and should compile and run successfully if everything was setup properly.
```cpp
#include <PixelEngine.h>

void Main()
{
	Pixel::App* app = new Pixel::App();
	app->CreateWindow("Hello World!", 800, 600);
	Pixel::RenderService::Singleton()->Initialize();
	app->SetWindowVisible(true);
	app->StartGameLoop();
	delete app;
}

PixelMain(Main);
```