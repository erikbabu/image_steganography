#include <iostream>
#include <memory>
#include "PicUtils.hpp"
#include "Picture.hpp"

using std::vector;
using std::cout;
using std::endl;
using std::runtime_error;
using std::string;
using cv::Mat;
using cv::imread;
using cv::imwrite;
using std::shared_ptr;
using std::make_shared;
using std::cerr;
using std::bitset;

Mat PicUtils::createImage(int width, int height)
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

int PicUtils::saveImage(Mat img, string filename)
{
  vector<int> compression_params;

  compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
  compression_params.push_back(95);

  try{
    imwrite(filename, img, compression_params);
  }catch (runtime_error& ex) {
    fprintf(stderr, "Exception converting image to JPEG format: %s\n",
          ex.what());
    return 1;
  }

  return 0;
}

Mat PicUtils::loadImage(string path)
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

void encryptImage(const string& image_filename, const string& text_filename)
{
  //load the source image
  auto img = make_shared<Picture>(image_filename);

  int height = img->getHeight();
  int width = img->getWidth();

  //get the binary representation of the text file contents
  auto binary_contents = getBinaryFileContents(text_filename);
  //check that message is not too long to be encrypted
  checkFullMessageCanBeEncrypted(binary_contents.size(), height, width);

  auto binary_iter = binary_contents.begin();
  int binary_counter = UNICODE_BITS;

  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      Colour current = img->getPixel(x, y);

      if (binary_iter != binary_contents.end())
      {
        //get current binary value to encode
        int bit_value = (*binary_iter)[--binary_counter];
        //update the Least significant bit to be encoded value
        int updated_Blue = getModifiedLSB(bit_value, current.getBlue());
        current.setBlue(updated_Blue);
        img->setPixel(x, y, current);
        updateBinaryEncIterator(binary_counter, binary_iter);
      }
      else
      {
        break;
      }
    }
  }

  saveEncryptedImage(img->getImage());
}

void checkFullMessageCanBeEncrypted(string::size_type message_len,
    int width, int height)
{
  auto num_pixels = (unsigned) width * height;
  auto overhead = (unsigned) strlen(END_OF_MESSAGE);

  if (message_len + overhead > num_pixels)
  {
    cout << "Sorry. The message is too long to be encrypted in this file."
      << " Either use an image with larger dimensions or text with "
      << "less than or equal to " << num_pixels << " characters." << endl;
    exit(1);
  }
}

template<class Iterator> void updateBinaryEncIterator(int& count, Iterator& iter)
{
  if (count == 0)
  {
    count = UNICODE_BITS;
    ++iter;
  }
}

int getModifiedLSB(int bit_value, int blue_value)
{
  if (bit_value == 1)
  {
    //edge case. If 0 needs to be made odd, it should only go up
    if (blue_value == 0) return blue_value + 1;
    return (blue_value % 2 != 0) ? blue_value : blue_value - 1;
  }

  //bit_value is 0
  //edge case. If 255 needs to be made even, it should only go down
  if (blue_value == 255) return blue_value - 1;
  return (blue_value % 2 == 0) ? blue_value : blue_value + 1;
}

void decryptImage(const string& image_filename)
{
  auto img = make_shared<Picture>(image_filename);

  int height = img->getHeight();
  int width = img->getWidth();

  vector<char> decrypted;

  int binary_counter = UNICODE_BITS;
  bitset<UNICODE_BITS> char_binary;
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      Colour current = img->getPixel(x, y);
      //decrypted value is either 1 or 0 on lsb of colour component
      int bin_val = current.getBlue() % 2;
      char_binary[--binary_counter] = bin_val;
      updateBinaryDecCounter(binary_counter, decrypted, char_binary);
    }
  }

  //convert vector<char> to string
  string decrypted_text(decrypted.begin(), decrypted.end());
  //remove the end of message key word
  string formatted_result = decryptedMessage(decrypted_text);
  saveDecryptedText(formatted_result);
}

void updateBinaryDecCounter(int& counter, std::vector<char>& decrypted,
  std::bitset<UNICODE_BITS>& binary)
{
  if (counter == 0)
  {
    //store char representation of binary in vector
    decrypted.push_back(convertBinToChar(binary));
    //reset counter and bitset
    counter = UNICODE_BITS;
    binary.reset();
  }
}

string decryptedMessage(string& decrypted)
{
  string::size_type n;
  // search backwards from end of string for end of message keyword
  n = decrypted.rfind(END_OF_MESSAGE);

  if (n == string::npos) {
    cout << decrypted << endl;
    cerr << "End of message key word not found. Decryption failed!" << endl;
    exit(1);
  }

  return decrypted.substr(0, n);
}
