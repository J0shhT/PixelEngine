/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Core/UserInputService.h
*/

#pragma once

#include "Include/Common.h"

#include <gainput/gainput.h>
#include <wx/defs.h>

namespace Pixel {

	/**
	*  A unique ID binded to a specific event callback in the UserInputService.
	*/
	typedef std::string InputEventCallbackId;

	/**
	*  Keyboard keys, see the gainput library documentation
	for gainput::Key for a list of available keys.
	*/
	typedef gainput::Key Key;

	/**
	*  Mouse buttons, see the gainput library documentation
	for gainput::MouseButton for a list of available buttons.
	*/
	typedef gainput::MouseButton MouseButton;

	/**
	*  Gamepad buttons, see the gainput library documentation
	for gainput::PadButton for a list of available buttons.
	*/
	typedef gainput::PadButton GamepadButton;

	/**
	*  The different types of input events handled by UserInputService.
	*/
	enum class InputEventType
	{
		KeyDown, //* Invoked when a key on the keyboard is pressed into a down state.
		KeyUp, //* Invoked when a key on the keyboard is released from a down state.
		MouseDown, //* Invoked when a button on the mouse is pressed into a down state.
		MouseUp, //* Invoked when a button on the mouse is released from a down state.
		MouseMove, //* Invoked when the mouse changes its position.
		GamepadDown, //* Invoked when a button on the gamepad is pressed into a down state.
		GamepadUp, //* Invoked when a button on the gamepad is released from a down state.
	};

	/**
	*  The Pixel::InputEvent struct is a container for general input events
	that have been invoked. All input events use this struct to send their
	information to callback functions.
	*  Only some properties of this struct will be used depending on the type of event.
	*/
	struct InputEvent
	{
		/**
		*  The type of input this InputEvent is representing.
		*/
		Pixel::InputEventType inputType;

		/**
		*  The Pixel::Key code the event occured on.
		*  This property is only applicable to:
		- InputEventType::KeyDown
		- InputEventType::KeyUp
		*/
		Pixel::Key key;

		/**
		*  The Pixel::MouseButton code the event occured on.
		*  This property is only applicable to:
		- InputEventType::MouseDown
		- InputEventType::MouseUp
		*/
		Pixel::MouseButton mouseButton;

		/**
		*  The Pixel::GamepadButton the event occured on.
		*  This property is only applicable to:
		- InputEventType::GamepadDown
		- InputEventType::GamepadUp
		*/
		Pixel::GamepadButton gamepadButton;

		/**
		*  The X coordinate of the mouse position, relative to the window.
		*  This property is only applicable to:
		- InputEventType::MouseMove
		- InputEventType::MouseDown
		- InputEventType::MouseUp
		*/
		unsigned int mouseX;

		/**
		*  The Y coordinate of the mouse position, relative to the window.
		*  This property is only applicable to:
		- InputEventType::MouseMove
		- InputEventType::MouseDown
		- InputEventType::MouseUp
		*/
		unsigned int mouseY;
	};

	/**
	*  The required function prototype for input event callbacks.
	*/
	typedef void InputEventCallback(const Pixel::InputEvent&);

	/**
	*  The Pixel::UserInputService is a singleton service used to detect,
	handle, and expose input from various devices from the user.
	*  This service allows you to bind functions to invoke when certain
	input events occur.
	*  This service abstracts the complication of detecting input
	depending on what windowing subsystem you are using (SDL vs wxWidgets)
	*  Depending on what windowing subsystem you use, input is detected
	in a different way, but is abstracted via this service to one standard.
	*  See Pixel::InputEventType enum for supported input events.

	!!! IMPORTANT !!!
	SDL and wxWidgets subsystems currently support different inputs from
	one another. Some inputs may invoke differently or not at all
	depending on what window subsystem you are using.

	* SDL currently supports:
	- All events in the Pixel::InputEventType enum
	- IsKeyDown() with all keys

	* wxWidgets currently supports:
	- MouseMove
	- MouseDown & MouseUp, but only for Button0, Button1, Button2, Button5, and Button6
	- KeyDown & KeyUp, but only the ASCII keys (32 to 96)
	- IsKeyDown() with the ASCII keys (32 to 96)
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
			*  Updates and fetches various input from the user.
			*/
			void Update();

			/**
			*  Returns whether or not the specified key is in a down state.
			*/
			bool IsKeyDown(Pixel::Key) const;

			/**
			*  Binds the specified InputEventCallback function to invoke when
			the specified InputEventType is signaled.
			*  Returns an InputEventCallbackId which is a unique ID representing
			the binded callback function. Use this ID to unbind the callback.
			*/
			InputEventCallbackId Bind(InputEventType, InputEventCallback*);

			/**
			*  Unbinds the callback specified by the InputEventCallbackId that
			is binded to the specified InputEventType.
			*/
			void Unbind(InputEventType, InputEventCallbackId id);

		private:

			struct InputListener;

			void _callConnectedCallbacks(Pixel::InputEventType, Pixel::InputEvent&);

			void _signalMouseMove(unsigned int mouseX, unsigned int mouseY);
			void _signalMouseDown(Pixel::MouseButton);
			void _signalMouseUp(Pixel::MouseButton);

			void _signalKeyDown(Pixel::Key);
			void _signalKeyUp(Pixel::Key);

			void _signalGamepadDown(Pixel::GamepadButton);
			void _signalGamepadUp(Pixel::GamepadButton);

			void _signalDeviceButtonDown(gainput::DeviceId device, gainput::DeviceButtonId deviceButton);
			void _signalDeviceButtonUp(gainput::DeviceId device, gainput::DeviceButtonId deviceButton);

			std::map<InputEventType, std::map<InputEventCallbackId, InputEventCallback*>> _connectedCallbacks;
			std::map<Pixel::Key, bool> _activeKeys;
			std::map<wxKeyCode, bool> _activeWxKeys;

			gainput::InputManager* _inputManager;
			InputListener* _listener;

			gainput::DeviceId _mouseDeviceId;
			gainput::DeviceId _keyboardDeviceId;
			gainput::DeviceId _gamepadDeviceId;

			unsigned int _mouseX;
			unsigned int _mouseY;

	};

}