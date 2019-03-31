Ryan Conway - G00332826

GMIT Galway

## Theroy of Algorithms Project

In this project we were required to write a program in the C programming language that calculated the SHA-256 
checksum of an input. The program is specified in the Secure Hash Standard document supplied by the US National Institute
of Standards and Technology[1].

### Implementation and Development

This Project was developed on a linux vm supplied by the Google Cloud Platform using the C language. [Using the Secure Hash Standard](https://www.nist.gov/publications/secure-hash-standard)[1] we were tasked with recreating the SHA-256 in C using this as  a guide. Lectures and Videos from Dr Ian McLoughin were a massive help throughout delevopment with researching the SHA algorithm and teaching us the fundimentals of C.[2]

### Compiling the program:

To compile this program, the user must clone this repository by running:
  
  - git clone https://github.com/RCElucidator7/TOA-Project.git
  
Once in the repository, the user can run the command 

  - "gcc -o sha256.c sha256"
  
(Assuming the user has a GCC compiler.) The name of 
your runnable can be anything but for this example I have used 'sha256'.

### Running the Program:

To run the program, the user must choose a file to hash (must be in this repository if you have your own file). If you do not
have a file some test files are included. Once the file is ready, run with the following command:

  - "./sha256 test1.txt". 

The program should output the 
SHA256 checksum of that input.

### Testing the program:

To test the accuracy of this program, I have included some test cases and a file with the desired output of these test cases.
If you have your own file you would like to test you can [use this link](https://emn178.github.io/online-tools/sha256_checksum.html "SHA256 File Checksum").[3]

### End Notes

While completing the algorithm I compared my results to desired output of test case files from the internet and discovered that these outputs do not match my own. I revised through my code and changes some things but I cannot identify a clear problem. It may be a machine problem but I cannot be certain.

Overall this was a fun and enjoyable project to code up, learning about the Secure Hash Algorithm and all that it can be used for.

### References

  - [Secure Hash Standard](https://www.nist.gov/publications/secure-hash-standard) 1
  - [Video Lectures from Dr Ian McLoughin](https://web.microsoftstream.com/video/db7c03be-5902-4575-9629-34d176ff1366) 2
  - [SHA 256 Checksum](https://emn178.github.io/online-tools/sha256_checksum.html) 3
