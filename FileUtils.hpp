#include <vector>
#include <bitset>
#include <fstream>

#define MAX_ASCII_VAL 128
#define ASCII_BITS 8

//returns contents of ascii text file in binary representation
std::vector<std::bitset<ASCII_BITS> > getBinaryFileContents(const std::string& filename);

//ensures that the file exists and can be opened for reading
std::ifstream validateFile(const std::string& filename);

//reads all text (including whitespace) in a file and returns the result
std::string getStringFileContents(std::ifstream& inputFile);

//ensures that every character in the input file is ASCII
void checkFileContainsOnlyAscii(const std::string& fileContents);

//given 8 bit binary, returns char representation
char convertBinToChar(const std::bitset<ASCII_BITS>& bin_rep);

//ensures that file extension is supported by encoder/decoder
void checkValidFileExtension(const std::string& filename);

//returns file extension
std::string getExtension(const std::string& filename);
