#include "Include/Object/Object.h"

#include "Include/PixelOutput.h"

PIXEL_DECLARE_OBJECT(Object);

Pixel::Object::Object::Object()
{
	PIXEL_OBJECT_CONSTRUCTOR(Object);
	std::ostringstream strStream;
	strStream << "Object::Object() - Created " << this;
	Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Debug, strStream.str().c_str());
}

Pixel::Object::Object::~Object()
{
	std::ostringstream strStream;
	strStream << "Object::Object() - Destroyed " << this;
	Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Debug, strStream.str().c_str());
	PIXEL_OBJECT_DECONSTRUCTOR(Object);
}

std::string Pixel::Object::Object::GetId() const
{
	return _id;
}

double Pixel::Object::Object::GetAge() const
{
	std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::high_resolution_clock::now();
	return static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(now - _createdAt).count()) / 1000000.0;
}

std::string Pixel::Object::Object::GetName() const
{
	return _name;
}

void Pixel::Object::Object::SetName(const std::string &name)
{
	_name = name;
}

bool Pixel::Object::Object::IsDeleted()
{
	return _isDeleted;
}
