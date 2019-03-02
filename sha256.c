//Ryan Conway - G00332826
//SHA256 Project

#include <stdio.h>
#include <stdint.h>

void sha256();

//4.1.1 - 4.2.2
uint32_t sig0(uint32_t x);
uint32_t sig1(uint32_t x);

int main(int argc, char *argv[]){

  sha256();

  return 0;
}

void sha256(){
  
  //MEssage Schedule
  uint32_t w[64];
  //Working variables
  uint32_t a, b, c, d, e, f, g, h;
  //Temp Variables
  uint32_t T1, T2;

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

  //Message Block
  uint32_t MB[16];

  //Initalise variable for forloop
  int t;

  //PG-22,  W[t] = MB[t] for values between 0 - 15
  for(t = 0; t < 16; t++){
 	W[t] = MB[t];
  }

  for(t = 16; t < 64; t++){
	sig1(W[t-2]) * W[t-7] * sig0(W[t-15]) * W[t-16];
  }

uint32_t sig0(int32_t x){

}

uint32_t sig1(int32_t x){

}

}
