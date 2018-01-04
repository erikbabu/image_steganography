#ifndef PIC_UTILS_GUARD_H
#define PIC_UTILS_GUARD_H

#include <opencv2/opencv.hpp>
#include <bitset>
#include <vector>
#include "FileUtils.hpp"

class PicUtils{

 public:

  //Creates a new picture with specified width and height
  cv::Mat createImage(int width, int height);

  //saves image (JPEG) with the given filename
  int saveImage(cv::Mat img, std::string filename);

  //loads image at specified path (can be url or filesystem location)
  cv::Mat loadImage(std::string path);

};

//reads the input from the textfile and encrypts that data into the image file
void encryptImage(const std::string& image_filename, const std::string& text_filename);

//helper function for encryptImage. It updates the counter that reads from
//the binary representation of the text file
template<typename Iterator> void updateBinaryEncIterator(int& count, Iterator& iter);

//returns the Blue component that has its lsb set to the value that needs to be encoded
int getModifiedLSB(int bit_value, int blue_value);

//given an image, decrypts the text if image is valid and stores the result in a text file
void decryptImage(const std::string& image_filename);

//helper for decryptImage. Returns the decrypted string without the end of message keyword
std::string decryptedMessage(std::string& decrypted);

//helper for decryptImage. Keeps track of a counter that places the bits
//in the correct indices of the bitset
void updateBinaryDecCounter(int& counter, std::vector<char>& decrypted,
  std::bitset<UNICODE_BITS>& binary);

#endif
