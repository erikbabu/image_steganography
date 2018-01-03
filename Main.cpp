#include <iostream>
#include "FileUtils.hpp"
#include "PicUtils.hpp"

using std::cout;
using std::endl;

int main(int argc, char **argv)
{
  auto filename = argv[1];

  auto contents = getBinaryFileContents(filename);
  //display intro (show user which characters can be encryted/decrypted)

  //get max number of characters that can be encrypted and inform user

  //collect and validate message to be encrypted

  //encrypt message

  //save image


  return 0;
}
