#include "Include/Type/Position.h"

Pixel::Type::Position::Position() : _x{ 0.0 }, _y{ 0.0 }
{
}

Pixel::Type::Position::Position(double xy) : _x{ xy }, _y{ xy }
{
}

Pixel::Type::Position::Position(double x, double y) : _x{ x }, _y{ y }
{
}

Pixel::Type::Position::~Position()
{
}

Pixel::Type::Position Pixel::Type::Position::operator+(const Pixel::Type::Position& other) const
{
	Pixel::Type::Position position;
	position._x = _x + other._x;
	position._y = _y + other._y;
	return position;
}

Pixel::Type::Position Pixel::Type::Position::operator-(const Pixel::Type::Position& other) const
{
	Pixel::Type::Position position;
	position._x = _x - other._x;
	position._y = _y - other._y;
	return position;
}

Pixel::Type::Position Pixel::Type::Position::operator*(const Pixel::Type::Position& other) const
{
	Pixel::Type::Position position;
	position._x = _x * other._x;
	position._y = _y * other._y;
	return position;
}

Pixel::Type::Position Pixel::Type::Position::operator/(const Pixel::Type::Position& other) const
{
	Pixel::Type::Position position;
	position._x = _x / other._x;
	position._y = _y / other._y;
	return position;
}

Pixel::Type::Position Pixel::Type::Position::operator-() const
{
	Pixel::Type::Position position;
	position._x = -(_x);
	position._y = -(_y);
	return position;
}

bool Pixel::Type::Position::operator==(const Pixel::Type::Position& other) const
{
	return (_x == other._x) && (_y == other._y);
}

bool Pixel::Type::Position::operator!=(const Pixel::Type::Position& other) const
{
	return !((*this) == other);
}

bool Pixel::Type::Position::operator>(const Pixel::Type::Position& other) const
{
	return GetMagnitude() > other.GetMagnitude();
}

bool Pixel::Type::Position::operator>=(const Pixel::Type::Position& other) const
{
	return ((*this) > other) || (GetMagnitude() == other.GetMagnitude());
}

bool Pixel::Type::Position::operator<(const Pixel::Type::Position& other) const
{
	return !((*this) >= other);
}

bool Pixel::Type::Position::operator<=(const Pixel::Type::Position& other) const
{
	return !((*this) > other);
}

void Pixel::Type::Position::Set(double x, double y)
{
	_x = { x };
	_y = { y };
}

void Pixel::Type::Position::Set(double xy)
{
	_x = { xy };
	_y = { xy };
}

void Pixel::Type::Position::SetX(double value)
{
	_x = { value };
}

void Pixel::Type::Position::SetY(double value)
{
	_y = { value };
}

double Pixel::Type::Position::GetX() const
{
	return _x;
}

double Pixel::Type::Position::GetY() const
{
	return _y;
}

double Pixel::Type::Position::GetArea() const
{
	return _x * _y;
}

double Pixel::Type::Position::GetMagnitude() const
{
	return sqrt((_x * _x) + (_y * _y));
}

std::string Pixel::Type::Position::ToString() const
{
	return std::string("(") + std::to_string(_x) + std::string(", ") + std::to_string(_y) + std::string(")");
}
