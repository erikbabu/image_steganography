#include <algorithm>
#include <math.h>
#include "Colour.hpp"

using std::min;

Colour::Colour(int red, int green, int blue){
  this->red = red;
  this->green = green;
  this->blue = blue;
  this->hsi_red = transformedValue(red);
  this->hsi_green = transformedValue(green);
  this->hsi_blue = transformedValue(blue);
  calculateHue();
  calculateSaturation();
  calculateIntensity();
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

void Colour::calculateHue()
{
  long numerator = 0.5 * ((hsi_red - hsi_green) + (hsi_red - hsi_blue));
    
  long denominator = pow(hsi_red - hsi_green, 2.0);
  denominator += (hsi_red - hsi_blue) * (hsi_green - hsi_blue);
  denominator = pow(denominator, 0.5);

  long result = acos(numerator / denominator);


  if (hsi_blue > hsi_green)
  {
    result = 2 * M_PI - result;
  }

  //normalise result to be in range [0..360]
  result = (result * PI_RAD) / M_PI;
  hue = result;
}

void Colour::calculateSaturation()
{
  long result = 1 - min({hsi_red, hsi_green, hsi_blue});
  //normalise result to be within the range [0..100]
  saturation = result * 100;
}

void Colour::calculateIntensity()
{
  long result = (hsi_red + hsi_green + hsi_blue) / 
    (NUM_COMPONENTS * MAX_INTENSITY);
  //normalise result to be within range [0,255]
  intensity = result * 255;
}

int Colour::gethue() const
{
  return hue;
}

int Colour::getsaturation() const
{
  return saturation;
}

int Colour::getintensity() const
{
  return intensity;
}

void Colour::sethue(int value)
{
  hue = value;
}

void Colour::setsaturation(int value)
{
  saturation = value;
}

void Colour::setintensity(int value)
{
  intensity = value;
}

long Colour::transformedValue(int value)
{
  return value / (red + green + blue);
}
