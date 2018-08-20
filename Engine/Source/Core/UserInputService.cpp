#include "Include/Core/UserInputService.h"

#include "Include/PixelError.h"

#include "Include/Core/PixelApp.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>

#include <wx/wx.h>

struct Pixel::UserInputService::InputListener : public gainput::InputListener
{
	InputListener()
	{

	}

	virtual ~InputListener()
	{

	}

	bool OnDeviceButtonBool(gainput::DeviceId device, gainput::DeviceButtonId deviceButton, bool oldValue, bool newValue)
	{
		if (newValue == true)
		{
			Pixel::UserInputService::Singleton()->_signalDeviceButtonDown(device, deviceButton);
		}
		else
		{
			Pixel::UserInputService::Singleton()->_signalDeviceButtonUp(device, deviceButton);
		}
		return true;
	}

	bool OnDeviceButtonFloat(gainput::DeviceId device, gainput::DeviceButtonId deviceButton, float oldValue, float newValue)
	{
		return true;
	}
};


PIXEL_DECLARE_SINGLETON(Pixel::UserInputService);

Pixel::UserInputService::UserInputService()
{
	PIXEL_SINGLETON_CONSTRUCTOR(Pixel::UserInputService);

	_inputManager = new gainput::InputManager(true, gainput::GetDefaultAllocator());

	_mouseDeviceId = _inputManager->CreateDevice<gainput::InputDeviceMouse>();
	_keyboardDeviceId = _inputManager->CreateDevice<gainput::InputDeviceKeyboard>();
	_gamepadDeviceId = _inputManager->CreateDevice<gainput::InputDevicePad>();

	_listener = new Pixel::UserInputService::InputListener();
	_inputManager->AddListener(_listener);
}

Pixel::UserInputService::~UserInputService()
{
	delete _listener;
	delete _inputManager;
	PIXEL_SINGLETON_DECONSTRUCTOR(Pixel::UserInputService);
}

void Pixel::UserInputService::Update()
{
	static Pixel::App* app = Pixel::App::Singleton();

	//Update mouse position
	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(app->GetWindowHandle(), &mousePos);
	unsigned int mouseX;
	unsigned int mouseY;
	if (mousePos.x <= 0)
	{
		mouseX = 0;
	}
	else
	{
		if (mousePos.x >= app->GetWindowWidth())
		{
			mouseX = app->GetWindowWidth();
		}
		else
		{
			mouseX = mousePos.x;
		}
	}
	if (mousePos.y < 0)
	{
		mouseY = 0;
	}
	else
	{
		if (mousePos.y >= app->GetWindowHeight())
		{
			mouseY = app->GetWindowHeight();
		}
		else
		{
			mouseY = mousePos.y;
		}
	}
	if (mouseX != _mouseX || mouseY != _mouseY)
		_signalMouseMove(mouseX, mouseY);
	_mouseX = mouseX;
	_mouseY = mouseY;

	if (app->IsSDL())
	{
		//Update gainput
		MSG msg;
		_inputManager->Update();
		while (PeekMessage(&msg, app->GetWindowHandle(), 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			_inputManager->HandleMessage(msg);
		}

		//Process SDL events
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				case SDL_QUIT:
					app->Close();
					break;
			}
		}
	}
	else if (app->IsWxWidgets())
	{
		static bool wasMouseLeftDown = false;
		static bool wasMouseRightDown = false;
		static bool wasMouseMiddleDown = false;
		static bool wasMouseAux1Down = false;
		static bool wasMouseAux2Down = false;

		wxMouseState mouseState = wxGetMouseState();

		//Left mouse button
		if (mouseState.LeftIsDown())
		{
			if (!wasMouseLeftDown)
				_signalMouseDown(Pixel::MouseButton::MouseButton0);
			wasMouseLeftDown = true;
		}
		else
		{
			if (wasMouseLeftDown)
				_signalMouseUp(Pixel::MouseButton::MouseButton0);
			wasMouseLeftDown = false;
		}

		//Middle mouse button
		if (mouseState.MiddleIsDown())
		{
			if (!wasMouseMiddleDown)
				_signalMouseDown(Pixel::MouseButton::MouseButton1);
			wasMouseMiddleDown = true;
		}
		else
		{
			if (wasMouseMiddleDown)
				_signalMouseUp(Pixel::MouseButton::MouseButton1);
			wasMouseMiddleDown = false;
		}

		//Right mouse button
		if (mouseState.RightIsDown())
		{
			if (!wasMouseRightDown)
				_signalMouseDown(Pixel::MouseButton::MouseButton2);
			wasMouseRightDown = true;
		}
		else
		{
			if (wasMouseRightDown)
				_signalMouseUp(Pixel::MouseButton::MouseButton2);
			wasMouseRightDown = false;
		}

		//Aux1 mouse button
		if (mouseState.Aux1IsDown())
		{
			if (!wasMouseAux1Down)
				_signalMouseDown(Pixel::MouseButton::MouseButton5);
			wasMouseAux1Down = true;
		}
		else
		{
			if (wasMouseAux1Down)
				_signalMouseUp(Pixel::MouseButton::MouseButton5);
			wasMouseAux1Down = false;
		}

		//Aux2 mouse button
		if (mouseState.Aux2IsDown())
		{
			if (!wasMouseAux2Down)
				_signalMouseDown(Pixel::MouseButton::MouseButton6);
			wasMouseAux2Down = true;
		}
		else
		{
			if (wasMouseAux2Down)
				_signalMouseUp(Pixel::MouseButton::MouseButton6);
			wasMouseAux2Down = false;
		}

		//standard ASCII keys (key 32 to 96)
		for (size_t key = 32; key <= 96; key++)
		{
			wxKeyCode keyCode = wxKeyCode(key);
			//Add key to map if it's not in there yet
			if (_activeWxKeys.find(keyCode) == _activeWxKeys.end())
			{
				_activeWxKeys[keyCode] = false;
			}

			//Check key state
			if (wxGetKeyState(keyCode))
			{
				if (_activeWxKeys[keyCode] == false)
					_signalKeyDown((Pixel::Key)key);
				_activeWxKeys[keyCode] = true;
			}
			else
			{
				if (_activeWxKeys[keyCode] == true)
					_signalKeyUp((Pixel::Key)key);
				_activeWxKeys[keyCode] = false;
			}
		}
	}
}

enum KeyConversionTable
{

};
wxKeyCode convertToWxKey(Pixel::Key key)
{
	if (key >= 32 && key <= 96)
	{
		return wxKeyCode(key);
	}
	else
	{
		PixelError("Failed to convert Pixel::Key " + std::to_string(key) + " to a wxKeyCode");
		return wxKeyCode::WXK_NONE;
	}
}

bool Pixel::UserInputService::IsKeyDown(Pixel::Key key) const
{
	static Pixel::App* app = Pixel::App::Singleton();
	if (app->IsSDL())
	{
		if (_activeKeys.find(key) == _activeKeys.end())
		{
			return false;
		}
		else
		{
			return _activeKeys.at(key);
		}
	}
	else if (app->IsWxWidgets())
	{
		wxKeyCode wxKey = convertToWxKey(key);
		if (_activeWxKeys.find(wxKey) == _activeWxKeys.end())
		{
			return false;
		}
		else
		{
			return _activeWxKeys.at(wxKey);
		}
	}
}

std::string Pixel::UserInputService::Bind(InputEventType type, InputEventCallback* callback)
{
	if (_connectedCallbacks.find(type) == _connectedCallbacks.end())
	{
		_connectedCallbacks[type] = std::map<std::string, InputEventCallback*>();
	}
	std::string uid = boost::lexical_cast<std::string>(boost::uuids::random_generator()());
	_connectedCallbacks[type][uid] = callback;
	return uid;
}

void Pixel::UserInputService::Unbind(InputEventType type, const std::string& id)
{
	if (_connectedCallbacks.find(type) != _connectedCallbacks.end())
	{
		if(_connectedCallbacks[type].find(id) != _connectedCallbacks[type].end())
		{
			_connectedCallbacks[type].erase(id);
		}
		else
		{
			PixelError("UserInputService::Unbind() - No event connected with id \"" + id + "\" (InputEventType " + std::to_string((int)type) + ")");
			return;
		}
	}
	else
	{
		PixelError("UserInputService::Unbind() - No event connected with id \"" + id + "\" (InputEventType " + std::to_string((int)type) + ")");
		return;
	}
}

void Pixel::UserInputService::_callConnectedCallbacks(Pixel::InputEventType eventType, Pixel::InputEvent& e)
{
	auto callbacksEntry = _connectedCallbacks.find(eventType);
	if (callbacksEntry != _connectedCallbacks.end())
	{
		//Call all binded function callbacks
		auto callbacks = callbacksEntry->second;
		for (auto iter = callbacks.cbegin(); iter != callbacks.cend(); ++iter)
		{
			iter->second(e);
		}
	}
}

void Pixel::UserInputService::_signalMouseMove(unsigned int mouseX, unsigned int mouseY)
{
	Pixel::InputEvent e;
	e.inputType = Pixel::InputEventType::MouseMove;
	e.mouseX = mouseX;
	e.mouseY = mouseY;
	_callConnectedCallbacks(Pixel::InputEventType::MouseMove, e);
}

void Pixel::UserInputService::_signalMouseDown(Pixel::MouseButton mouseButton)
{
	Pixel::InputEvent e;
	e.inputType = Pixel::InputEventType::MouseDown;
	e.mouseX = _mouseX;
	e.mouseY = _mouseY;
	e.mouseButton = mouseButton;
	_callConnectedCallbacks(Pixel::InputEventType::MouseDown, e);
}

void Pixel::UserInputService::_signalMouseUp(Pixel::MouseButton mouseButton)
{
	Pixel::InputEvent e;
	e.inputType = Pixel::InputEventType::MouseUp;
	e.mouseX = _mouseX;
	e.mouseY = _mouseY;
	e.mouseButton = mouseButton;
	_callConnectedCallbacks(Pixel::InputEventType::MouseUp, e);
}

void Pixel::UserInputService::_signalKeyDown(Pixel::Key key)
{
	_activeKeys[key] = true;
	Pixel::InputEvent e;
	e.inputType = Pixel::InputEventType::KeyDown;
	e.key = key;
	_callConnectedCallbacks(Pixel::InputEventType::KeyDown, e);
}

void Pixel::UserInputService::_signalKeyUp(Pixel::Key key)
{
	_activeKeys[key] = false;
	Pixel::InputEvent e;
	e.inputType = Pixel::InputEventType::KeyUp;
	e.key = key;
	_callConnectedCallbacks(Pixel::InputEventType::KeyUp, e);
}

void Pixel::UserInputService::_signalGamepadDown(Pixel::GamepadButton button)
{
	Pixel::InputEvent e;
	e.inputType = Pixel::InputEventType::GamepadDown;
	e.gamepadButton = button;
	_callConnectedCallbacks(Pixel::InputEventType::GamepadDown, e);
}

void Pixel::UserInputService::_signalGamepadUp(Pixel::GamepadButton button)
{
	Pixel::InputEvent e;
	e.inputType = Pixel::InputEventType::GamepadUp;
	e.gamepadButton = button;
	_callConnectedCallbacks(Pixel::InputEventType::GamepadUp, e);
}

void Pixel::UserInputService::_signalDeviceButtonDown(gainput::DeviceId device, gainput::DeviceButtonId deviceButton)
{
	if (device == _mouseDeviceId)
	{
		_signalMouseDown((Pixel::MouseButton)deviceButton);
	}
	else if (device == _keyboardDeviceId)
	{
		_signalKeyDown((Pixel::Key)deviceButton);
	}
	else if (device == _gamepadDeviceId)
	{
		_signalGamepadDown((Pixel::GamepadButton)deviceButton);
	}
	else
	{
		PixelWarning("UserInputService::InputListener signaled event from unknown device (" + std::to_string(device) + ")");
		return;
	}
}

void Pixel::UserInputService::_signalDeviceButtonUp(gainput::DeviceId device, gainput::DeviceButtonId deviceButton)
{
	if (device == _mouseDeviceId)
	{
		_signalMouseUp((Pixel::MouseButton)deviceButton);
	}
	else if (device == _keyboardDeviceId)
	{
		_signalKeyUp((Pixel::Key)deviceButton);
	}
	else if (device == _gamepadDeviceId)
	{
		_signalGamepadUp((Pixel::GamepadButton)deviceButton);
	}
	else
	{
		PixelWarning("UserInputService::InputListener signaled event from unknown device (" + std::to_string(device) + ")");
		return;
	}
}