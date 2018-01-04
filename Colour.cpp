#include "Colour.hpp"

Colour::Colour(int red, int green, int blue){
  this->red = red;
  this->green = green;
  this->blue = blue;
}

int Colour::getRed() const
{
  return red;
}

int Colour::getGreen() const
{
  return green;
}

int Colour::getBlue() const
{
  return blue;
}

void Colour::setBlue(int value)
{
  blue = value;
}
