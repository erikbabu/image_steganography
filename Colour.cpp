#include "Colour.hpp"

Colour::Colour(int red, int green, int blue){
  this->red = red;
  this->green = green;
  this->blue = blue;
}

int Colour::getred(){
  return red; 
}

int Colour::getgreen(){
  return green; 
}

int Colour::getblue(){
  return blue; 
}

void Colour::setred(int value){
  red = value; 
}

void Colour::setgreen(int value){
  green = value; 
}


void Colour::setblue(int value){
  blue = value; 
}
