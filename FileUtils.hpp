#include <vector>
#include <bitset>
#include <fstream>

#define MAX_ASCII_VAL 128
#define ASCII_BITS 8

std::vector<std::bitset<ASCII_BITS> > getBinaryFileContents(const std::string& filename);
std::ifstream validateFile(const std::string& filename);
std::string getStringFileContents(std::ifstream& inputFile);
void checkFileContainsOnlyAscii(const std::string& fileContents);
char convertBinToChar(const std::bitset<ASCII_BITS>& bin_rep);
void checkValidFileExtension(const std::string& filename);
std::string getExtension(const std::string& filename);


