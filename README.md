Ryan Conway - G00332826

GMIT Galway

## Theroy of Algorithms Project

In this project we were required to write a program in the C programming language that calculated the SHA-256 
checksum of an input. The program is specified in the Secure Hash Standard document supplied by the US National Institute
of Standards and Technology.

#### Compiling the program:

To compile this program, the user must clone this repository by running:
  
  - git clone https://github.com/RCElucidator7/TOA-Project.git
  
Once in the repository, the user can run the command "gcc -o sha256.c sha256", assuming the user has a GCC compiler. The name of 
your runnable can be anything but for this example I have used 'sha256'.

#### Running the Program:

To run the program, the user must choose a file to hash (must be in this repository if you have your own file). If you do not
have a file some test files are included. Once the file is ready, run with "sha256 test1.txt". The program should output the 
SHA256 checksum of that input.

#### Testing the program:
To test the accuracy of this program, I have included some test cases and a file with the desired output of these test cases.
If you have your own file you would like to test you can [use this link](https://emn178.github.io/online-tools/sha256_checksum.html "SHA256 File Checksum")

