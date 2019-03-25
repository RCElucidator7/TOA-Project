#include<stdio.h>
#include<stdint.h>

union messageblock {
    uint8_t b[64];
    uint32_t mb[16];
    uint64_t pad[8];
};

int main(int argc, char *argv[]){

    union messageblock MB;

    uint64_t nobytes;

    //Padder
    uint64_t nobits = 0;

    FILE* f;

    f = fopen(argv[1], "r");

    while (!feof(f)){
	nobytes = fread(MB.b, 1, 64, f);
	nobits = nobits + (nobytes * 8);
	if(nobytes < 56){
	    printf("Block with less than 55 bytes found.\n");
	    //1 is on the right
	    MB.b[nobytes] = 0x01;
	    //1 is on the left
	    //MB.b[nobytes] = 0x80;
	    while (nobytes < 56){
	        nobytes = nobytes + 1;
		MB.b[nobytes] = 0x00;
	    }
	    MB.pad[7] = nobits;
	}
    }

    fclose(f);
    
    for(int i = 0; i < 64; i++){
	printf("%x ", MB.b[i]);
    }
    printf("\n");
    
    return 0;
}
