Ryan Conway - G00332826

GMIT Galway

## Theroy of Algorithms Project

In this project we were required to write a program in the C programming language that calculated the SHA-256 
checksum of an input. The program is specified in the Secure Hash Standard document supplied by the US National Institute
of Standards and Technology[1].

### Implementation and Development

This Project was developed on a linux vm supplied by the Google Cloud Platform using the C language. [Using the Secure Hash Standard](https://www.nist.gov/publications/secure-hash-standard)[1] we were tasked with recreating the SHA-256 in C using this as  a guide. Lectures and Videos from Dr Ian McLoughin were a massive help throughout delevopment with researching the SHA algorithm and teaching us the fundimentals of C.[2]

### How it Works

- The Program begins with the main() method. This takes in a file name (which must be passed in when running the program).
- It attempts to open this file while checking for errors. If there are any errors an error message is desplayed and the program exits, if there are no errors it continues.
- It then executes the sha256() method which is where the computation of the final hash value takes place.

##### sha256()
- The sha265 method starts with defining all the constants it needs according to the secure hash standard[1] Such as the first 64 prime numbers in hex (K) and the variable which will be used as out output (H). 
- The method then enters a while loop which calls the function nextMessageblock() (As seen below).
- In this loop is where the hashing takes place, using the functions shr() and rotr() which will shift and rotate the position of the bytes as needed. 
- Then, using K, more methods are called to generate out output. (Ch(), Maj(), SIG0(), SIG1(), sig0(), sig1()).
- Once this is computed the values are assigned in order to the H variable for output.
- Before these values are output, the program checks if the system is in Big or Little Endian as our desired output must be in big endian. If its a case where the values are Little Endian, a SWAP_UINT32 method is called which switches each hex value from Little to Big Endian.
- Once the values are output to the screen, the program returns to the main method.
- In the main method the file is closed and the program exits.

##### nextMessageblock()
- The nextMessageblock method takes in 4 parameters, the file, a variable of type messageblock, an enum Status, and a uint variables nobits.
- This method reads in message blocks in 64 byte chunks from the file.
- It keeps doing this until either a block with less than 56 bytes is read in or a block with between 56 and 64 bytes is read in.
- In the first case, it pads the remaining bytes with zeros and returns to the sha256 method.
- In the second case, it pads the remaining bytes with zeros, it sets the status to PAD0 which tells the program to create the next message block and only pad it with zeros.
- If the block contains exactly 64 bytes, it sets the status to PAD1 which changes the first byte to 1 and pads the rest with zeros.
- Whens theres no more padding to be done the status is set to finish and it returns to the sha method.

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
