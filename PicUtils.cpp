#include <iostream>
#include <vector>
#include "PicUtils.hpp"

using std::vector;
using std::cout;
using std::endl;
using std::runtime_error;
using std::string;
using cv::Mat;
using cv::imread;
using cv::imwrite;

Mat PicUtils::createimage(int width, int height)
{
  Mat img;
  try {
    cout <<"creating colour image" << endl;
    img.create(height, width, CV_8UC3);
  } catch (runtime_error& ex) {
    fprintf(stderr, "Exception creating color image: %s\n", ex.what());
    return 1;
  }

  return img;
}

int PicUtils::saveimage(Mat img, string filename)
{
  vector<int> compression_params;

  compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
  compression_params.push_back(100);

  try{
    imwrite(filename, img, compression_params);
  }catch (runtime_error& ex) {
    fprintf(stderr, "Exception converting image to JPEG format: %s\n",
          ex.what());
    return 1;
  }

  return 0;
}

Mat PicUtils::loadimage(string path)
{
  Mat img;
  try{
    img = imread(path, CV_LOAD_IMAGE_COLOR);
    if (!img.data) cout <<"Could not load the image" << endl;
  }catch (runtime_error& ex) {
    fprintf(stderr, " %s\n", ex.what());
    return 1;
  }

  return img;
}
