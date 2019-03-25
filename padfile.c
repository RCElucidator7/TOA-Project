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

    FILE* f;

    f = fopen(argv[1], "r");

    while (!feof(f)){
	nobytes = fread(MB.b, 1, 64, f);
	printf("%llu \n", nobytes);
    }

    fclose(f);
    return 0;
}
