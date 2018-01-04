#include <vector>
#include <bitset>
#include <fstream>
#include "PicUtils.hpp"

#define MAX_UNICODE_VAL 65535
#define UNICODE_BITS 16
//terminating string to notify that end of output has been reached during
//decryption
#define END_OF_MESSAGE "DISCOMBOBULATE"

//returns contents of unicode text file in binary representation
std::vector<std::bitset<UNICODE_BITS> > getBinaryFileContents(const std::string& filename);

//ensures that the file exists and can be opened for reading
std::ifstream validateFile(const std::string& filename);

//reads all text (including whitespace) in a file and returns the result
std::string getStringFileContents(std::ifstream& inputFile);

//ensures that every character in the input file is UNICODE
void checkFileContainsOnlyUnicode(const std::string& fileContents);

//given 16 bit binary, returns char representation
char convertBinToChar(const std::bitset<UNICODE_BITS>& bin_rep);

//ensures that file extension is supported by encoder/decoder
void checkValidFileExtension(const std::string& filename);

//returns file extension
std::string getExtension(const std::string& filename);

//given a Mat file, saves the image to a specific location
void saveEncryptedImage(const cv::Mat& img);

//saves the given string to a text file with a specific filename
void saveDecryptedText(std::string& formatted_result);
