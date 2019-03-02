//Ryan Conway - G00332826
//SHA256 Project

#include <stdio.h>
#include <stdint.h>

void sha256();

//4.1.1 - 4.2.2
uint32_t sig0(uint32_t x);
uint32_t sig1(uint32_t x);

//3.2
uint32_t rotr(uint32_t n, uint32_t x);
uint32_t shr(uint32_t n, uint32_t x);

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

  a = H[0];
  b = H[1];
  c = H[2];
  d = H[3];
  e = H[4];
  f = H[5];
  g = H[6];
  h = H[7];

  for(t = 0; t < 64; t ++){
	T1 = h + SIG_1(e) + Ch(e, f, g) + K[t] + W[t];
	T2 = SIG_0(a) + Maj(a, b, c);
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

uint32_t sig0(int32_t x){
  return (rotr(7, x) ^ rotr(18, x) ^ shr(3, x));
}

uint32_t sig1(int32_t x){
  return (rotr(17, x) ^ rotr(19, x) ^ shr(3, x));
}

uint32_t rotr(uint32_t n, uint32_t x){
  return (x >> n) | (x << (32 - n));
}

uint32_t shr(uint32_t n, uint32_t x){
  return (x >> n);
}
