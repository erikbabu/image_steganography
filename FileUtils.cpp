#include <iostream>
#include <set>
#include <sstream>
#include "FileUtils.hpp"

using std::set;
using std::vector;
using std::string;
using std::ifstream;
using std::cerr;
using std::cout;
using std::endl;
using std::stringstream;
using std::bitset;
using cv::Mat;
using std::ofstream;

vector<bitset<UNICODE_BITS> > getBinaryFileContents(const string& filename)
{
  auto input_file = validateFile(filename);
  string file_contents = getStringFileContents(input_file) + END_OF_MESSAGE;
  checkFileContainsOnlyUnicode(file_contents);

  //container to store the binary representation of the input
  vector<bitset<UNICODE_BITS> > ret;

  for (auto c : file_contents)
  {
    ret.push_back(bitset<UNICODE_BITS>(c));
  }

  return ret;
}

ifstream validateFile(const string& filename)
{
  checkValidFileExtension(filename);
  ifstream input_file;
  input_file.open(filename);

  if (!input_file)
  {
    cerr << "Unable to open file: " << filename << endl;
    exit(1);
  }

  return input_file;
}

string getStringFileContents(ifstream& input_file)
{
  stringstream buffer;
  buffer << input_file.rdbuf();

  return buffer.str();
}

void checkFileContainsOnlyUnicode(const string& file_contents)
{
  for(char current : file_contents)
  {
    uint16_t current_index = current;
    if (current_index < 0 || current_index > MAX_UNICODE_VAL)
    {
      cerr << "The following character index: " << current_index
        << " is out of UNICODE range!";
      exit(1);
    }
  }
}

char convertBinToChar(const bitset<UNICODE_BITS>& bin_rep)
{
  return (uint16_t)(bin_rep.to_ulong());
}

void checkValidFileExtension(const string& filename)
{
  //currently only supports text file conversion
  static set<string> valid_extensions = { "txt" };

  if (valid_extensions.find(getExtension(filename)) ==
        valid_extensions.end())
  {
    cerr << "Sorry. This is not a supported file extension at this time. "
      << "The following extensions are supported:" << endl;
    for (auto ext : valid_extensions) cerr << ext << endl;
    exit(1);
  }
}

string getExtension(const string& filename)
{
  string::size_type last_dot;
  last_dot = filename.rfind('.');

  if(last_dot != string::npos)
  {
    return filename.substr(last_dot + 1);
  }
  else
  {
    cerr << "Error: No extension found!" << endl;
    exit(1);
  }
}

void saveEncryptedImage(const Mat& img)
{
  auto encrypted_image_filename = "embedded_image.png";
  PicUtils picUtils;
  picUtils.saveImage(img, encrypted_image_filename);
  cout << "Encryption completed!" << endl;
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
