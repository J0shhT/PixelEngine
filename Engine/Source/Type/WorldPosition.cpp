#include "Include/Type/WorldPosition.h"

Pixel::Type::WorldPosition::WorldPosition() : Pixel::Type::Position()
{
}

Pixel::Type::WorldPosition::WorldPosition(double xy) : Pixel::Type::Position(xy)
{
}

Pixel::Type::WorldPosition::WorldPosition(double x, double y) : Pixel::Type::Position(x, y)
{
}

Pixel::Type::WorldPosition::~WorldPosition()
{
}
