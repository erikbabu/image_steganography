#ifndef COLOUR_GUARD_H
#define COLOUR_GUARD_H

#define MAX_INTENSITY 255

//Represents a pixel of an image in RGB format
class Colour {

  public:

  // class constructor (sets all attributes)
  Colour(int red, int green, int blue);

  // returns pixel intensity for different RGB colour components
  int getRed() const;
  int getGreen() const;
  int getBlue() const;

  // sets pixel intensity for specific colour component containing colour
  //representation's LSB
  void setBlue(int value);

  private:

    // internal representation of pixel intensities for RGB
    int red;
    int green;
    int blue;

};

#endif
