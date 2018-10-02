/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Source/Object/BasicTextGui.cpp
*/

#include "Include/Object/BasicTextGui.h"

#include "Include/PixelOutput.h"

PIXEL_DECLARE_OBJECT(BasicTextGui);

Pixel::Object::BasicTextGui::BasicTextGui()
{
	PIXEL_OBJECT_CONSTRUCTOR(BasicTextGui);
	_text = "BasicTextGui";
	_position = Pixel::Type::Position(0.0f);
	_textColor = Pixel::Type::Color(0.0f);
}

Pixel::Object::BasicTextGui::~BasicTextGui()
{
	PIXEL_OBJECT_DECONSTRUCTOR(BasicTextGui);
}

void Pixel::Object::BasicTextGui::SetText(const std::string& text)
{
	_text = text;
}

void Pixel::Object::BasicTextGui::SetPosition(Pixel::Type::Position position)
{
	_position = position;
}

void Pixel::Object::BasicTextGui::SetTextColor(Pixel::Type::Color color)
{
	_textColor = color;
}

std::string Pixel::Object::BasicTextGui::GetText() const
{
	return _text;
}

Pixel::Type::Position Pixel::Object::BasicTextGui::GetPosition() const
{
	return _position;
}

Pixel::Type::Color Pixel::Object::BasicTextGui::GetTextColor() const
{
	return _textColor;
}

void Pixel::Object::BasicTextGui::Render()
{
	glColor3f(_textColor.GetRed(), _textColor.GetGreen(), _textColor.GetBlue());
	glRasterPos2f(_position.GetX(), _position.GetY());
	for (auto iter = _text.cbegin(); iter != _text.cend(); iter++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *iter);
	}
}