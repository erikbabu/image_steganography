#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include "FileUtils.hpp"
#include "PicUtils.hpp"
#include "Picture.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::shared_ptr;
using std::make_shared;
using std::string;
using cv::Mat;
using std::bitset;
using std::vector;
using std::ofstream;

static PicUtils picUtils;

void displayInstructions();
void encryptImage(const string& imageFilename, const string& textFilename);
void saveEncryptedImage(const Mat& img);
template<typename Iterator> void updateBinaryIterator(int& count, Iterator& iter);
int getModifiedLSB(int bit_value, int blue_value);
void decryptImage(const string& imageFilename);
string decryptedMessage(string& decrypted);
void saveDecryptedText(string& formatted_result);

int main(int argc, char **argv)
{
  if (argc > 3 || argc < 2) displayInstructions();

  auto imageFilename = argv[1];
  auto textFilename = argv[2];

  argc == 3 ? encryptImage(imageFilename, textFilename) : decryptImage(imageFilename);

  return 0;
}

void displayInstructions()
{
  cout << "program invocation should either be- \n"
    << "1) Encrypting: ./img_steg image_file text_file\n"
    << "2) Decrypting: ./img_steg image_file"
    << endl;
}

void encryptImage(const string& imageFilename, const string& textFilename)
{
  auto og = make_shared<Picture>(imageFilename);

  int height = og->getheight();
  int width = og->getwidth();

  auto binary_contents = getBinaryFileContents(textFilename);

  auto binary_iter = binary_contents.begin();
  int binary_counter = UNICODE_BITS;

  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      Colour current = og->getpixel(x, y);

      if (binary_iter != binary_contents.end())
      {
        int bit_value = (*binary_iter)[--binary_counter];
        int updated_Blue = getModifiedLSB(bit_value, current.getblue());
        Colour updated_colour(current.getred(), current.getgreen(), updated_Blue);
        og->setpixel(x, y, updated_colour);
        updateBinaryIterator(binary_counter, binary_iter);
      }
      else
      {
        break;
      }
    }
  }

  saveEncryptedImage(og->getimage());
}

template<class Iterator> void updateBinaryIterator(int& count, Iterator& iter)
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
    if (blue_value == 0) return blue_value + 1;
    return (blue_value % 2 != 0) ? blue_value : blue_value - 1;
  }

  if (blue_value == 255) return blue_value - 1;
  return (blue_value % 2 == 0) ? blue_value : blue_value + 1;
}

void saveEncryptedImage(const Mat& img)
{
  auto encrypted_image_filename = "embedded_image.png";
  picUtils.saveimage(img, encrypted_image_filename);
  cout << "Encryption completed!" << endl;
}

void decryptImage(const string& imageFilename)
{
  auto og = make_shared<Picture>(imageFilename);

  int height = og->getheight();
  int width = og->getwidth();

  vector<char> decrypted;

  int binary_counter = UNICODE_BITS;
  bitset<UNICODE_BITS> char_binary;
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      Colour current = og->getpixel(x, y);
      int bin_val = current.getblue() % 2;
      char_binary[--binary_counter] = bin_val;

      if (binary_counter == 0)
      {
        decrypted.push_back(convertBinToChar(char_binary));
        binary_counter = UNICODE_BITS;
        char_binary.reset();
      }
    }
  }

  string decrypted_text(decrypted.begin(), decrypted.end());
  string formatted_result = decryptedMessage(decrypted_text);
  saveDecryptedText(formatted_result);
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

void saveDecryptedText(string& formatted_result)
{
  auto decrypted_filename = "decrypted_output.txt";

  //write to file
  ofstream output_file (decrypted_filename);
  if (output_file.is_open())
  {
    output_file << formatted_result;
    output_file.close();
  }
  else cout << "Unable to open file";

  cout << "Decryption completed!" << endl;
}
