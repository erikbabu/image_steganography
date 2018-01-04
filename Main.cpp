#include <iostream>
#include "PicUtils.hpp"

using std::cout;
using std::endl;

//shows user how program should be correctly invoked
void displayInstructions();

int main(int argc, char **argv)
{
  if (argc > 3 || argc < 2) 
  {
    displayInstructions();
    exit(1);
  }

  auto image_filename = argv[1];
  auto text_filename = argv[2];

  argc == 3 ? encryptImage(image_filename, text_filename) : decryptImage(image_filename);

  return 0;
}

void displayInstructions()
{
  cout << "program invocation should either be- \n"
    << "1) Encrypting: ./img_steg image_file text_file\n"
    << "2) Decrypting: ./img_steg image_file"
    << endl;
}
