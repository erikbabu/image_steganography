#include <iostream>
#include <set>
#include <sstream>
#include "FileUtils.hpp"

using std::set;
using std::vector;
using std::string;
using std::ifstream;
using std::cerr;
using std::endl;
using std::stringstream;
using std::bitset;

vector<bitset<ASCII_BITS> > getBinaryFileContents(const string& filename)
{
  auto inputFile = validateFile(filename);
  string fileContents = getStringFileContents(inputFile);
  checkFileContainsOnlyAscii(fileContents);

  //container to store the binary representation of the input
  vector<bitset<ASCII_BITS> > ret;

  for (auto c : fileContents)
  {
    ret.push_back(bitset<ASCII_BITS>(c));
  }

  return ret;
}

ifstream validateFile(const string& filename)
{
  checkValidFileExtension(filename);
  ifstream inputFile;
  inputFile.open(filename);

  if (!inputFile)
  {
    cerr << "Unable to open file: " << filename << endl;
    exit(1);
  }

  return inputFile;
}

string getStringFileContents(ifstream& inputFile)
{
  stringstream buffer;
  buffer << inputFile.rdbuf();

  return buffer.str();
}

void checkFileContainsOnlyAscii(const string& fileContents)
{
  for(auto current : fileContents) 
  {
    if (current < 0 || current > MAX_ASCII_VAL)
    {
      cerr << "The following character: " << current
        << " is out of ASCII range!";
      exit(1);
    }
  }
}


char convertBinToChar(const bitset<8>& bin_rep)
{
  return (int)(bin_rep.to_ulong());
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
