#include "Include/Core/UserInputService.h"

#include "Include/PixelError.h"

#include "Include/Core/PixelApp.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>

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

	//Update gainput InputManager
	_inputManager->Update();

	//Send Windows messages to gainput
	MSG msg;
	while (PeekMessage(&msg, app->GetWindowHandle(), 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		_inputManager->HandleMessage(msg);
	}
}

std::string Pixel::UserInputService::Bind(InputEventType type, InputEventCallback* callback)
{
	if (Pixel::App::Singleton()->IsWxWidgets())
	{
		PixelWarning("UserInputService does not have support for wxWidgets window subsystem currently");
		return "";
	}
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
			PixelWarning("UserInputService::Unbind() - No event connected with id \"" + id + "\" (InputEventType " + std::to_string((int)type) + ")");
			return;
		}
	}
	else
	{
		PixelWarning("UserInputService::Unbind() - No event connected with id \"" + id + "\" (InputEventType " + std::to_string((int)type) + ")");
		return;
	}
}

void Pixel::UserInputService::_signalDeviceButtonDown(gainput::DeviceId device, gainput::DeviceButtonId deviceButton)
{
	Pixel::InputEventType type;
	if (device == _mouseDeviceId)
	{
		type = Pixel::InputEventType::MouseDown;
	}
	else if (device == _keyboardDeviceId)
	{
		type = Pixel::InputEventType::KeyDown;
	}
	else if (device == _gamepadDeviceId)
	{
		type = Pixel::InputEventType::GamepadDown;
	}
	else
	{
		PixelWarning("UserInputService - InputListener signaled event from unknown device (" + std::to_string(device) + ")");
		return;
	}

	auto callbacksEntry = _connectedCallbacks.find(type);
	if (callbacksEntry != _connectedCallbacks.end())
	{
		//Call all binded function callbacks
		auto callbacks = callbacksEntry->second;
		for (auto iter = callbacks.cbegin(); iter != callbacks.cend(); ++iter)
		{
			Pixel::InputEvent e;
			e.inputType = type;
			if (type == Pixel::InputEventType::MouseDown)
			{
				e.mouseButton = (Pixel::MouseButton)deviceButton;
				e.mouseX = _mouseX;
				e.mouseY = _mouseY;
			}
			else if (type == Pixel::InputEventType::KeyDown)
			{
				e.key = (Pixel::Key)deviceButton;
			}
			else if (type == Pixel::InputEventType::GamepadDown)
			{
				e.gamepadButton = (Pixel::GamepadButton)deviceButton;
			}
			iter->second(e);
		}
	}
}

void Pixel::UserInputService::_signalDeviceButtonUp(gainput::DeviceId device, gainput::DeviceButtonId deviceButton)
{
	Pixel::InputEventType type;
	if (device == _mouseDeviceId)
	{
		type = Pixel::InputEventType::MouseUp;
	}
	else if (device == _keyboardDeviceId)
	{
		type = Pixel::InputEventType::KeyUp;
	}
	else if (device == _gamepadDeviceId)
	{
		type = Pixel::InputEventType::GamepadUp;
	}
	else
	{
		PixelWarning("UserInputService - InputListener signaled event from unknown device (" + std::to_string(device) + ")");
		return;
	}

	auto callbacksEntry = _connectedCallbacks.find(type);
	if (callbacksEntry != _connectedCallbacks.end())
	{
		//Call all binded function callbacks
		auto callbacks = callbacksEntry->second;
		for (auto iter = callbacks.cbegin(); iter != callbacks.cend(); ++iter)
		{
			Pixel::InputEvent e;
			e.inputType = type;
			if (type == Pixel::InputEventType::MouseUp)
			{
				e.mouseButton = (Pixel::MouseButton)deviceButton;
				e.mouseX = _mouseX;
				e.mouseY = _mouseY;
			}
			else if (type == Pixel::InputEventType::KeyUp)
			{
				e.key = (Pixel::Key)deviceButton;
			}
			else if (type == Pixel::InputEventType::GamepadUp)
			{
				e.gamepadButton = (Pixel::GamepadButton)deviceButton;
			}
			iter->second(e);
		}
	}
}

void Pixel::UserInputService::_signalMouseMove(unsigned int mouseX, unsigned int mouseY)
{
	auto callbacksEntry = _connectedCallbacks.find(Pixel::InputEventType::MouseMove);
	if (callbacksEntry != _connectedCallbacks.end())
	{
		//Call all binded function callbacks
		auto callbacks = callbacksEntry->second;
		for (auto iter = callbacks.cbegin(); iter != callbacks.cend(); ++iter)
		{
			Pixel::InputEvent e;
			e.inputType = Pixel::InputEventType::MouseMove;
			e.mouseX = mouseX;
			e.mouseY = mouseY;
			iter->second(e);
		}
	}
}