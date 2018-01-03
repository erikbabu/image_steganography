#include "Picture.hpp"

using std::string;
using cv::Mat;

Picture::Picture(string path)
{
  img = imgio.loadimage(path);
}

Picture::Picture(int width, int height)
{
  img = imgio.createimage(width, height);
}

int Picture::getwidth()
{
  return img.size().width;
}

int Picture::getheight()
{
  return img.size().height;
}

Colour Picture::getpixel(int x, int y)
{
  //opencv pixels stored as (y,x) vector
  cv::Vec3b pixel = img.at<cv::Vec3b>(y,x);
  Colour rgb(pixel[RED], pixel[GREEN],pixel[BLUE]);
  return rgb;
}

void Picture::setpixel(int x, int y, Colour rgb)
{
  //opencv pixels stored as (y,x) vector
  img.at<cv::Vec3b>(y,x)[BLUE] = rgb.getblue();
  img.at<cv::Vec3b>(y,x)[GREEN] = rgb.getgreen();
  img.at<cv::Vec3b>(y,x)[RED] = rgb.getred();
}

Mat Picture::getimage()
{
  return img;
}
