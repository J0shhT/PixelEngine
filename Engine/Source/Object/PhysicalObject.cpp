/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Source/Object/PhysicalObject.cpp
*/

#include "Include/Object/PhysicalObject.h"

#include "Include/PixelOutput.h"

PIXEL_DECLARE_OBJECT(PhysicalObject);

Pixel::Object::PhysicalObject::PhysicalObject()
{
	PIXEL_OBJECT_CONSTRUCTOR(PhysicalObject);
	_position = Pixel::Type::WorldPosition(0.0);
	_size = Pixel::Type::Size(100.0);
	_color = Pixel::Type::Color(1.0, 1.0, 1.0);
	_isSolid = true;
	_isAnchored = false;
	_textureMode = Pixel::TextureMode::Stretch;
	_textureRepeatX = 1.0f;
	_textureRepeatY = 1.0f;
}

Pixel::Object::PhysicalObject::~PhysicalObject()
{
	PIXEL_OBJECT_DECONSTRUCTOR(PhysicalObject);
}

Pixel::Type::WorldPosition Pixel::Object::PhysicalObject::GetPosition() const
{
	return _position;
}

Pixel::Type::Size Pixel::Object::PhysicalObject::GetSize() const
{
	return _size;
}

Pixel::Type::Velocity Pixel::Object::PhysicalObject::GetVelocity() const
{
	return _velocity;
}

bool Pixel::Object::PhysicalObject::IsAnchored() const
{
	return _isAnchored;
}

bool Pixel::Object::PhysicalObject::IsSolid() const
{
	return _isSolid;
}

Pixel::Type::Color Pixel::Object::PhysicalObject::GetColor() const
{
	return _color;
}

std::string Pixel::Object::PhysicalObject::GetTexture() const
{
	if (_texture != "")
	{
		auto texture = Pixel::ContentProvider::Singleton()->Get(_texture);
		if (texture->type == Pixel::ContentType::Texture)
		{
			return texture->filePath;
		}
	}
	return "";
}

Pixel::TextureMode Pixel::Object::PhysicalObject::GetTextureMode() const
{
	return _textureMode;
}

float Pixel::Object::PhysicalObject::GetTextureRepeatX() const
{
	return _textureRepeatX;
}

float Pixel::Object::PhysicalObject::GetTextureRepeatY() const
{
	return _textureRepeatY;
}

void Pixel::Object::PhysicalObject::SetPosition(Pixel::Type::WorldPosition value)
{
	_position = value;
}

void Pixel::Object::PhysicalObject::SetSize(Pixel::Type::Size value)
{
	_size = value;
}

void Pixel::Object::PhysicalObject::SetVelocity(Pixel::Type::Velocity value)
{
	_velocity = value;
}

void Pixel::Object::PhysicalObject::SetAnchored(bool value)
{
	_isAnchored = value;
}

void Pixel::Object::PhysicalObject::SetSolid(bool value)
{
	_isSolid = value;
}

void Pixel::Object::PhysicalObject::SetColor(Pixel::Type::Color value)
{
	_color = value;
}

void Pixel::Object::PhysicalObject::SetTexture(std::string path)
{
	if (path.substr(0, 4) == "http")
	{
		//Texture is an online file
		Pixel::ContentId textureId = Pixel::ContentProvider::Singleton()->LoadTextureWeb(path);
		if (textureId != "")
		{
			_texture = textureId;
		}
	}
	else
	{
		//Texture is a local file
		Pixel::ContentId textureId = Pixel::ContentProvider::Singleton()->LoadTextureFile(path);
		if (textureId != "")
		{
			_texture = textureId;
		}
	}
}

void Pixel::Object::PhysicalObject::SetTextureMode(Pixel::TextureMode textureMode)
{
	_textureMode = textureMode;
}

void Pixel::Object::PhysicalObject::SetTextureRepeatX(float value)
{
	_textureRepeatX = value;
}

void Pixel::Object::PhysicalObject::SetTextureRepeatY(float value)
{
	_textureRepeatY = value;
}

void Pixel::Object::PhysicalObject::SetTextureRepeat(float x, float y)
{
	SetTextureRepeatX(x);
	SetTextureRepeatY(y);
}
void Pixel::Object::PhysicalObject::SetTextureRepeat(float xy)
{
	SetTextureRepeat(xy, xy);
}