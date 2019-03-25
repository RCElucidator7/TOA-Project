#include<stdio.h>
#include<stdint.h>

union messageblock {
    uint8_t b[64];
    uint32_t mb[16];
    uint64_t pad[8];
};

enum status {READ, PAD0, PAD1, FINISH};

int main(int argc, char *argv[]){

    union messageblock MB;

    //Number of bytes returned
    uint64_t nobytes;

    //Keep track of bits
    uint64_t nobits = 0;

    enum status S = READ;

    FILE* f;

    f = fopen(argv[1], "r");

    while (S == READ){
	nobytes = fread(MB.b, 1, 64, f);
	nobits = nobits + (nobytes * 8);
	if(nobytes < 56){
	    printf("Block with less than 55 bytes found.\n");
	    //Maybe read in an option for little or big edian
	    //1 is on the right (Big edian)
	    // MB.b[nobytes] = 0x01;
	    //1 is on the left (Little edian)
	    MB.b[nobytes] = 0x80;
	    while (nobytes < 56){
	        nobytes = nobytes + 1;
		MB.b[nobytes] = 0x00;
	    }
	    MB.pad[7] = nobits;
	    S = FINISH;
	} else if (nobytes < 64) {
	    S = PAD0;
	    MB.b[nobytes] = 0x80;
	    while (nobytes < 64){
		nobytes = nobytes + 1;
		MB.b[nobytes] = 0x00;
	    }
	} else if (feof(f)) {
	    S = PAD1;
	}
    }

    if (S == PAD0 || S == PAD1){
	for(int j = 0; j < 56; j++){
	    MB.b[j] = 0x00;
	}
	MB.pad[7] = nobits;
    }
    if (S == PAD1){
	MB.mb[0] = 0x80;
    }

    fclose(f);
    
    for(int i = 0; i < 64; i++){
	printf("%x ", MB.b[i]);
    }
    printf("\n");
    
    return 0;
}
