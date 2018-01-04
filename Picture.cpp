#include "Picture.hpp"

using std::string;
using cv::Mat;

Picture::Picture(string path)
{
  img = imgio.loadImage(path);
}

Picture::Picture(int width, int height)
{
  img = imgio.createImage(width, height);
}

int Picture::getWidth()
{
  return img.size().width;
}

int Picture::getHeight()
{
  return img.size().height;
}

Colour Picture::getPixel(int x, int y)
{
  //opencv pixels stored as (y,x) vector
  cv::Vec3b pixel = img.at<cv::Vec3b>(y,x);
  Colour rgb(pixel[RED], pixel[GREEN],pixel[BLUE]);
  return rgb;
}

void Picture::setPixel(int x, int y, Colour rgb)
{
  //opencv pixels stored as (y,x) vector
  img.at<cv::Vec3b>(y,x)[BLUE] = rgb.getBlue();
  img.at<cv::Vec3b>(y,x)[GREEN] = rgb.getGreen();
  img.at<cv::Vec3b>(y,x)[RED] = rgb.getRed();
}

Mat Picture::getImage()
{
  return img;
}
