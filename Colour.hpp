#ifndef COLOUR_GUARD_H
#define COLOUR_GUARD_H

#define MAX_INTENSITY 255
#define NUM_COMPONENTS 3
#define PI_RAD 180

//Represents a pixel of an image in RGB format
class Colour {

  public:

  // class constructor (sets all attributes)
  Colour(int red, int green, int blue);

  // returns pixel intensity for specific colour
  int getred() const;
  int getgreen() const;
  int getblue() const;

  //returns pixel intensity for HSI(Hue, Saturation, Intensity) color space
  int gethue() const;
  int getsaturation() const;
  int getintensity() const;

  // sets pixel intensity for specific RGB component
  void setred(int value);
  void setgreen(int value);
  void setblue(int value);

  //set pixel intensity for specific HSI component
  void sethue(int value);
  void setsaturation(int value);
  void setintensity(int value);

  private:

    // internal representation of pixel intensities for RGB
    int red;
    int green;
    int blue;

    //internal representation of pixel intensities for HSI
    int hue;
    int saturation;
    int intensity;

    //internal representation of HSI color space RGB values
    long hsi_red;
    long hsi_green;
    long hsi_blue;

    //returns the HSI R/G/B for a given R/G/B value
    long transformedValue(int value);

    void calculateHue();
    void calculateSaturation();
    void calculateIntensity();

};

#endif
