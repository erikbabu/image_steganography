# Image Steganography
Program that can hide text messages in images and also decrypt the text message hidden in an encrypted image. Implemented in C++ with aid of opencv library.

To use the program:

1) Run make (type 'make' into terminal. Requires opencv library to be installed on machine to work)

2) Invoke the program:

When encrypting: ./img_steg image_filename text_filename

When decrypting: ./img_step image_filename

3) View results: When encrypting, the output will be an image saved as 'embedded_image.png'. This image will have the secret text embedded. When decrypting, the output will be a text file saved as 'decrypted_output.txt'. This file will contain extracted text that was embedded in the image.

Note: If the image used for decryption has not been encrypted, the generated output will be garbage or the program will fail.

Algorithm inspired by:
A Novel Image Steganographic Approach for Hiding Text in Color Images using HSI Color Model

Khan Muhammad, Jamil Ahmad, Haleem Farman, Muhammad Zubair

arXiv:1503.00388 [cs.MM]
