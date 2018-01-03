#ifndef COLOUR_GUARD_H
#define COLOUR_GUARD_H

#define MAX_INTENSITY 255

//Represents a pixel of an image in RGB format
class Colour {

  public:

  // class constructor (sets all attributes)
  Colour(int red, int green, int blue);

  // returns pixel intensity for specific colour
  int getred();
  int getgreen();
  int getblue();

  // sets pixel intensity for specific colour
  void setred(int value);
  void setgreen(int value);
  void setblue(int value);

  private:

    // internal representation of pixel intensities for RGB
    int red;
    int green;
    int blue;

};

#endif
