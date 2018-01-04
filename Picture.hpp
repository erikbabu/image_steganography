#ifndef PICTURE_GUARD_H
#define PICTURE_GUARD_H

#include "Colour.hpp"
#include "PicUtils.hpp"

//Allows for image manipulation via the opencv lib
class Picture {

  public:

  enum RGB {BLUE, GREEN, RED};

  // loads an image from a provided file
  Picture(std::string path);

  // creates an empty image with the width and height dimensions provided
  Picture(int width, int height);

  // returns dimensions of image
  int getWidth();
  int getHeight();

  // returns single pixel from image represented as Colour
  Colour getPixel(int x, int y);

  // sets pixel in the image to provided colour
  void setPixel(int x, int y, Colour rgb);

  // provides the image of the class
  cv::Mat getImage();

  private:

  // opencv representation of an image
  cv::Mat img;
  PicUtils imgio;

 };

#endif
