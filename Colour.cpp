#include "Colour.hpp"

Colour::Colour(int red, int green, int blue){
  this->red = red;
  this->green = green;
  this->blue = blue;
}

int Colour::getred() const
{
  return red;
}

int Colour::getgreen() const
{
  return green;
}

int Colour::getblue() const
{
  return blue;
}

void Colour::setred(int value)
{
  red = value;
}

void Colour::setgreen(int value)
{
  green = value;
}

void Colour::setblue(int value)
{
  blue = value;
}
