#pragma once

#include "Include/Common.h"

#include <gainput/gainput.h>

namespace Pixel {

	typedef gainput::Key Key;
	typedef gainput::MouseButton MouseButton;
	typedef gainput::PadButton GamepadButton;

	/**
	*  TODO
	*/
	enum class InputEventType
	{
		KeyDown,
		KeyUp,
		MouseDown,
		MouseUp,
		MouseMove,
		GamepadDown,
		GamepadUp,
	};

	/**
	*  TODO
	*/
	struct PIXEL_API InputEvent
	{
		Pixel::InputEventType inputType; //* The type of input this InputEvent is representing
		Pixel::Key key; //* The number code for the key the event occured on (InputEventType::KeyDown or Input::EventType::KeyUp)
		Pixel::MouseButton mouseButton; //* The number code for the mouse button the event occured on (InputEventType::MouseDown or Input::EventType::MouseUp)
		Pixel::GamepadButton gamepadButton; //* The number code for the gamepad button the event occured on (InputEventType::GamepadDown or Input::EventType::GamepadUp)
		unsigned int mouseX; //* The X coordinate of the mouse position, relative to the window (InputEventType::MouseMove)
		unsigned int mouseY; //* The Y coordinate of the mouse position, relative to the window (InputEventType::MouseMove)
	};

	typedef void InputEventCallback(const Pixel::InputEvent&);

	/**
	*  TODO
	*/
	class PIXEL_API UserInputService final
	{

		PIXEL_DEFINE_SINGLETON(Pixel::UserInputService);

		public:

			/**
			*  Class constructor
			*/
			UserInputService();

			/**
			*  Class deconstructor
			*/
			~UserInputService();

			/**
			*  TODO
			*/
			void Update();

			/**
			*  TODO
			*/
			std::string Bind(InputEventType, InputEventCallback*);

			/**
			*  TODO
			*/
			void Unbind(InputEventType, const std::string& id);

		private:

			struct InputListener;

			void _signalDeviceButtonDown(gainput::DeviceId device, gainput::DeviceButtonId deviceButton);
			void _signalDeviceButtonUp(gainput::DeviceId device, gainput::DeviceButtonId deviceButton);
			void _signalMouseMove(unsigned int mouseX, unsigned int mouseY);

			std::map<InputEventType, std::map<std::string, InputEventCallback*>> _connectedCallbacks;

			gainput::InputManager* _inputManager;
			InputListener* _listener;

			gainput::DeviceId _mouseDeviceId;
			gainput::DeviceId _keyboardDeviceId;
			gainput::DeviceId _gamepadDeviceId;

			unsigned int _mouseX;
			unsigned int _mouseY;

	};

}