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
  int getwidth();
  int getheight();

  // returns single pixel from image represented as Colour
  Colour getpixel(int x, int y);

  // sets pixel in the image to provided colour
  void setpixel(int x, int y, Colour rgb);

  // checks if coordinates are within bounds of the stored image
  bool contains(int x, int y);

  // provides the image of the class
  cv::Mat getimage();

  // overwrites Picture image with another image
  void setimage(cv::Mat cpyimg);

  private:

  // opencv representation of an image
  cv::Mat img;
  PicUtils imgio;

 };

#endif
