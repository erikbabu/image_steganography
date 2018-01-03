#ifndef PIC_UTILS_GUARD_H
#define PIC_UTILS_GUARD_H

#include <opencv2/opencv.hpp>
#include <string>

class PicUtils{
    
 public:
   
  //Creates a new picture with specified width and height
  cv::Mat createimage(int width, int height);  

  //saves image (JPEG) with the given filename
  int saveimage(cv::Mat img, std::string filename);
  
  //loads image at specified path (can be url or filesystem location)
  cv::Mat loadimage(std::string path);
  
  
  //clones the img provided
  cv::Mat copyimage(cv::Mat img);
  
};

#endif
