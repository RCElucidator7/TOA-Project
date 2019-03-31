//Ryan Conway - G00332826
//SHA256 Project - Secure Hash Algorithm
//https://www.nist.gov/publications/secure-hash-standard

#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

//Union defined messageblock
//Used to access an 8 bit, 32 bit and 64 bit interger.
union messageblock {
    uint8_t b[64];
    uint32_t t[16];
    uint64_t s[8];
};

//Enum to keep track of what stage the program is in.
enum status {
    READ, 
    PAD0, 
    PAD1, 
    FINISH
};

//Error number
extern int errno;

//Initialize K
//4.2.2
uint32_t K[] = {
     0x428a2f98 ,0x71374491 ,0xb5c0fbcf ,0xe9b5dba5
     ,0x3956c25b ,0x59f111f1 ,0x923f82a4 ,0xab1c5ed5
     ,0xd807aa98 ,0x12835b01 ,0x243185be ,0x550c7dc3
     ,0x72be5d74 ,0x80deb1fe ,0x9bdc06a7 ,0xc19bf174
     ,0xe49b69c1 ,0xefbe4786 ,0x0fc19dc6 ,0x240ca1cc
     ,0x2de92c6f ,0x4a7484aa ,0x5cb0a9dc ,0x76f988da
     ,0x983e5152 ,0xa831c66d ,0xb00327c8 ,0xbf597fc7
     ,0xc6e00bf3 ,0xd5a79147 ,0x06ca6351 ,0x14292967
     ,0x27b70a85 ,0x2e1b2138 ,0x4d2c6dfc ,0x53380d13
     ,0x650a7354 ,0x766a0abb ,0x81c2c92e ,0x92722c85
     ,0xa2bfe8a1 ,0xa81a664b ,0xc24b8b70 ,0xc76c51a3
     ,0xd192e819 ,0xd6990624 ,0xf40e3585 ,0x106aa070
     ,0x19a4c116 ,0x1e376c08 ,0x2748774c ,0x34b0bcb5
     ,0x391c0cb3 ,0x4ed8aa4a ,0x5b9cca4f ,0x682e6ff3
     ,0x748f82ee ,0x78a5636f ,0x84c87814 ,0x8cc70208
     ,0x90befffa ,0xa4506ceb ,0xbef9a3f7 ,0xc67178f2
};

//Function to calculate the sha of a file passed in
void sha256(FILE *f);

//Function found at: http://www.firmcodes.com/write-c-program-convert-little-endian-big-endian-integer/
#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))
#define IS_BIG_ENDIAN (*(uint16_t *)"\0xff" < 0x100)

//------Functions used for hashing-------
//4.1.1 - 4.2.2
uint32_t sig0(uint32_t x);
uint32_t sig1(uint32_t x);

//3.2
uint32_t rotr(uint32_t n, uint32_t x);
uint32_t shr(uint32_t n, uint32_t x);

uint32_t SIG0(uint32_t x);
uint32_t SIG1(uint32_t x);

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z);

//To read in the next message block
int nextMessageblock(FILE *mfile, union messageblock *MB, enum status *S, uint64_t *nobits);

int main(int argc, char *argv[]){

  //Open the file given 
  FILE *mfile;
  mfile = fopen(argv[1], "r");

  //Error check to see if file is null
  if(mfile == NULL){
	fprintf(stderr, "Error opening file: %s\n", strerror( errno ));
  }
  else {
	//Call the SHA with passing in the file
	sha256(mfile);

	//Close the file
	fclose(mfile);
  }

  return 0;
}

void sha256(FILE *mfile){
  
  //Current message block
  union messageblock MB;

  //Number of bits read from the file
  uint64_t nobits = 0;

  //Current status of the message block
  enum status S = READ;

  //Message Schedule
  uint32_t W[64];
  //Working variables
  uint32_t a, b, c, d, e, f, g, h;
  //Temp Variables
  uint32_t T1, T2;
  //Initalise variable for forloop
  int i, j;

  //Hash Values 6.2
  //Values - 5.3.3
  uint32_t H[8] = {
	0x6a09e667,
	0xbb67ae85,
	0x3c6ef372,
	0xa54ff53a,
	0x510e527f,
	0x9b05688c,
	0x1f83d9ab,
	0x5be0cd19
  };

  while(nextMessageblock(mfile, &MB, &S, &nobits)){

    //PG-22,  W[t] = MB[t] for values between 0 - 15
    for(j = 0; j < 16; j++){
 	W[j] = MB.t[j];
    }

    for(j = 16; j < 64; j++){
	W[j] = sig1(W[j-2]) * W[j-7] * sig0(W[j-15]) * W[j-16];
    }

    a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];
    e = H[4];
    f = H[5];
    g = H[6];
    h = H[7];

    for(j = 0; j < 64; j++){
	T1 = h + SIG1(e) + Ch(e, f, g) + K[j] + W[j];
	T2 = SIG0(a) + Maj(a, b, c);
	h = g;
	g = f;
	f = e;
	e = d + T1;
	d = c;
	c = b;
	b = a;
	a = T1 + T2;
   }

    H[0] = a + H[0];
    H[1] = b + H[1];
    H[2] = c + H[2];
    H[3] = d + H[3];
    H[4] = e + H[4];
    H[5] = f + H[5];
    H[6] = g + H[6];
    H[7] = h + H[7];

  }

  printf("\n=======================HASH VALUES======================\n");

  //Check if the system is in big endian, if not convert little to big during output
  if(IS_BIG_ENDIAN){
    printf("\nSystem is in Big Endian\n");
    printf("%x%x%x%x%x%x%x%x\n", H[0], H[1], H[2], H[3], H[4], H[5], H[6], H[7]);
  }
  else{
    printf("\nSystem is in Little Endian - Converting results to Big Endian\n");
    printf("%x%x%x%x%x%x%x%x\n", SWAP_UINT32(H[0]), SWAP_UINT32(H[1]), SWAP_UINT32(H[2]), SWAP_UINT32(H[3]), SWAP_UINT32(H[4]), SWAP_UINT32(H[5]), SWAP_UINT32(H[6]), SWAP_UINT32(H[7]));
  }

  printf("\n========================================================\n");
}

uint32_t sig0(uint32_t x){
  return (rotr(7, x) ^ rotr(18, x) ^ shr(3, x));
}

uint32_t sig1(uint32_t x){
  return (rotr(17, x) ^ rotr(19, x) ^ shr(10, x));
}

uint32_t rotr(uint32_t n, uint32_t x){
  return ((x) >> (n)) | ((x) << (32 - (n)));
}

uint32_t shr(uint32_t n, uint32_t x){
  return ((x) >> n);
}

uint32_t SIG0(uint32_t x){
  return (rotr(2, x) ^ rotr(13, x) ^ rotr(22, x));
}

uint32_t SIG1(uint32_t x){
  return (rotr(6, x) ^ rotr(11, x) ^ rotr(25, x));
}

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z){
  return (((x) & (y)) ^ (~(x) & (z)));
}

uint32_t Maj(uint32_t x, uint32_t y, uint32_t z){
  return ((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z));
}

int nextMessageblock(FILE *mfile, union messageblock *MB, enum status *S, uint64_t *nobits){
    //Number of bytes in the current block
    uint64_t nobytes;

    //Loop count
    int i;

    //Return to main assuming all blocks are finished
    if(*S == FINISH){
      return 0;
    }

    //Check if a block needs padding
    if(*S == PAD0 || *S == PAD1){
    //Initalize the first 56 bits to 0
        for (i = 0; i < 56; i++){
            MB->b[i] = 0x00;
        }

	//Assign the last 64 bits to the number of bits in the file
	MB->s[7] = *nobits;
	*S = FINISH;

	//IF the status is in PAD1, set the first bit of the messageblock to 1
	if(*S == PAD1){
		MB->b[0] = 0x80;
	}

	return 1;
    }
	
    //Read in another block of data from the file
    nobytes = fread(MB->b, 1, 64, mfile);
    *nobits = *nobits + (nobytes * 8);

    //If a block with less than 55 bytes is found, apply the padding
    if(nobytes < 56){
	printf("Block with less than 55 bytes found\n");
	//Add a 1
	MB->b[nobytes] = 0x80;

	//Set the rest of the bits in the block to 0
	while(nobytes < 56) {
	    nobytes = nobytes + 1;
	    MB->b[nobytes] = 0x00;
	}
	MB->s[7] = *nobits;

	//Set the status to FINISH
	*S = FINISH;
    } else if(nobytes < 64) {
	*S = PAD0;

	//Add a 1
	MB->b[nobytes] = 0x80;

	//Set the rest of the bits in the block to 0
	while(nobytes < 64){
	    nobytes = nobytes + 1;
	    MB->b[nobytes] = 0x00;
	}
    } else if(feof(mfile)){
	*S = PAD1;
    }

    return 1;

}
