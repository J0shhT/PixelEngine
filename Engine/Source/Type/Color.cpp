#include "Include/Type/Color.h"

Pixel::Type::Color::Color() : _red{ 0.0 }, _green{ 0.0 }, _blue{ 0.0 }
{
}

Pixel::Type::Color::Color(double rgb) : _red{ rgb }, _green{ rgb }, _blue{ rgb }
{
}

Pixel::Type::Color::Color(unsigned char rgb) : _red{ (double)rgb / 255.0 }, _green{ (double)rgb / 255.0 }, _blue{ (double)rgb / 255.0 }
{
}

Pixel::Type::Color::Color(double r, double g, double b) : _red{ r }, _green{ g }, _blue{ b }
{
}

Pixel::Type::Color::Color(unsigned char r, unsigned char g, unsigned char b) : _red{ (double)r / 255.0 }, _green{ (double)b / 255.0 }, _blue{ (double)b / 255.0 }
{
}

Pixel::Type::Color::~Color()
{
}

Pixel::Type::Color Pixel::Type::Color::operator+(const Pixel::Type::Color& other) const
{
	Pixel::Type::Color color;
	color._red = _red + other._red;
	color._green = _green + other._green;
	color._blue = _blue + other._blue;
	return color;
}

Pixel::Type::Color Pixel::Type::Color::operator-(const Pixel::Type::Color& other) const
{
	Pixel::Type::Color color;
	color._red = _red - other._red;
	color._green = _green - other._green;
	color._blue = _blue - other._blue;
	return color;
}

Pixel::Type::Color Pixel::Type::Color::operator*(const Pixel::Type::Color& other) const
{
	Pixel::Type::Color color;
	color._red = _red * other._red;
	color._green = _green * other._green;
	color._blue = _blue * other._blue;
	return color;
}

Pixel::Type::Color Pixel::Type::Color::operator/(const Pixel::Type::Color& other) const
{
	Pixel::Type::Color color;
	color._red = _red / other._red;
	color._green = _green / other._green;
	color._blue = _blue / other._blue;
	return color;
}

bool Pixel::Type::Color::operator==(const Pixel::Type::Color& other) const
{
	return (_red == other._red) && (_green == other._green) && (_blue == other._blue);
}

bool Pixel::Type::Color::operator!=(const Pixel::Type::Color& other) const
{
	return !((*this) == other);
}

bool Pixel::Type::Color::operator>(const Pixel::Type::Color& other) const
{
	return GetLuminance() > other.GetLuminance();
}

bool Pixel::Type::Color::operator>=(const Pixel::Type::Color& other) const
{
	return ((*this) > other) || (GetLuminance() == other.GetLuminance());
}

bool Pixel::Type::Color::operator<(const Pixel::Type::Color& other) const
{
	return !((*this) >= other);
}

bool Pixel::Type::Color::operator<=(const Pixel::Type::Color& other) const
{
	return !((*this) > other);
}

void Pixel::Type::Color::Set(double r, double g, double b)
{
	_red = { r };
	_green = { g };
	_blue = { b };
}

void Pixel::Type::Color::Set(unsigned char r, unsigned char g, unsigned char b)
{
	_red = { (double)r / 255.0 };
	_green = { (double)g / 255.0 };
	_blue = { (double)b / 255.0 };
}

void Pixel::Type::Color::Set(double rgb)
{
	_red = { rgb };
	_green = { rgb };
	_blue = { rgb };
}

void Pixel::Type::Color::Set(unsigned char rgb)
{
	_red = { (double)rgb / 255.0 };
	_green = { (double)rgb / 255.0 };
	_blue = { (double)rgb / 255.0 };
}

void Pixel::Type::Color::SetRed(double value)
{
	_red = { value };
}

void Pixel::Type::Color::SetRed(unsigned char value)
{
	_red = { (double)value / 255.0 };
}

void Pixel::Type::Color::SetGreen(double value)
{
	_green = { value };
}

void Pixel::Type::Color::SetGreen(unsigned char value)
{
	_green = { (double)value / 255.0 };
}

void Pixel::Type::Color::SetBlue(double value)
{
	_blue = { value };
}

void Pixel::Type::Color::SetBlue(unsigned char value)
{
	_blue = { (double)value / 255.0 };
}

double Pixel::Type::Color::GetRed() const
{
	return _red;
}

double Pixel::Type::Color::GetGreen() const
{
	return _green;
}

double Pixel::Type::Color::GetBlue() const
{
	return _blue;
}

double Pixel::Type::Color::GetLuminance() const
{
	return sqrt(0.299 * pow(_red, 2) + 0.587 * pow(_green, 2) + 0.114 * pow(_blue, 2));
}

std::string Pixel::Type::Color::ToString() const
{
	return std::string("(") + std::to_string(_red) + std::string(", ") + std::to_string(_green) + std::string(", ") + std::to_string(_blue) + std::string(")");
}
