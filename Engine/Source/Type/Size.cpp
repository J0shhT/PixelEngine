/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Source/Type/Size.cpp
*/

#include "Include/Type/Size.h"

Pixel::Type::Size::Size() : _width{ 0.0 }, _height{ 0.0 }
{
}

Pixel::Type::Size::Size(double length) : _width{ length }, _height{ length }
{
}

Pixel::Type::Size::Size(double width, double height) : _width{ width }, _height{ height }
{
}

Pixel::Type::Size::~Size()
{
}

Pixel::Type::Size Pixel::Type::Size::operator+(const Pixel::Type::Size& other) const
{
	Pixel::Type::Size size;
	size._width = _width + other._width;
	size._height = _height + other._height;
	return size;
}

Pixel::Type::Size Pixel::Type::Size::operator-(const Pixel::Type::Size& other) const
{
	Pixel::Type::Size size;
	size._width = _width - other._width;
	size._height = _height - other._height;
	return size;
}

Pixel::Type::Size Pixel::Type::Size::operator*(const Pixel::Type::Size& other) const
{
	Pixel::Type::Size size;
	size._width = _width * other._width;
	size._height = _height * other._height;
	return size;
}

Pixel::Type::Size Pixel::Type::Size::operator/(const Pixel::Type::Size& other) const
{
	Pixel::Type::Size size;
	size._width = _width / other._width;
	size._height = _height / other._height;
	return size;
}

Pixel::Type::Size Pixel::Type::Size::operator-() const
{
	Pixel::Type::Size size;
	size._width = -(_width);
	size._height = -(_height);
	return size;
}

bool Pixel::Type::Size::operator==(const Pixel::Type::Size& other) const
{
	return (_width == other._width) && (_height == other._height);
}

bool Pixel::Type::Size::operator!=(const Pixel::Type::Size& other) const
{
	return !((*this) == other);
}

bool Pixel::Type::Size::operator>(const Pixel::Type::Size& other) const
{
	return GetArea() > other.GetArea();
}

bool Pixel::Type::Size::operator>=(const Pixel::Type::Size& other) const
{
	return ((*this) > other) || (GetArea() == other.GetArea());
}

bool Pixel::Type::Size::operator<(const Pixel::Type::Size& other) const
{
	return !((*this) >= other);
}

bool Pixel::Type::Size::operator<=(const Pixel::Type::Size& other) const
{
	return !((*this) > other);
}

void Pixel::Type::Size::Set(double width, double height)
{
	_width = { width };
	_height = { height };
}

void Pixel::Type::Size::Set(double xy)
{
	_width = { xy };
	_height = { xy };
}

void Pixel::Type::Size::SetWidth(double value)
{
	_width = { value };
}

void Pixel::Type::Size::SetHeight(double value)
{
	_height = { value };
}

double Pixel::Type::Size::GetWidth() const
{
	return _width;
}

double Pixel::Type::Size::GetHeight() const
{
	return _height;
}

double Pixel::Type::Size::GetArea() const
{
	return _width * _height;
}

std::string Pixel::Type::Size::ToString() const
{
	return std::string("(") + std::to_string(_width) + std::string(", ") + std::to_string(_height) + std::string(")");
}