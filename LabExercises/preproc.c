#include<stdio.h>
#include<inttypes.h>

#define BYTE uint8_t
#define WORD uint32_t
#define W 32
#define PF PRIX32

union Block {
    BYTE bytes[64];
    WORD words[16];
};

int main(int argc, char *argv[])
{
    union Block B;
    // Total number of bits read
    uint64_t nobits = 0;
    // File pointer for reading 
    FILE *f;
    // Open file from cmd line for reading
    f = fopen(argv[1], "r");
    // Number of bytes read
    size_t nobytes;
    
    // Try to read 64 bytes 
    nobytes = fread(B.bytes, 1, 64, f);
    // Tell the cmd line how many we read
    printf("Read %ld bytes.\n", nobytes);
    nobits += 8 * nobytes;

    // print the 16 32-bit words.
    for (int i = 0; i < 16; i++)
    {
        printf("%08" PF " ", B.words[i]);
        if ((i + 1) % 8 == 0)
            printf("\n"); 
    }

    while(!feof(f)) {
        // repeat ^
        nobytes = fread(&B.bytes, 1, 64, f);
        printf("Read %ld bytes.\n", nobytes);
        nobits += 8 * nobytes;

        // print the 16 32-bit words.
        for (int i = 0; i < 16; i++)
        {
            printf("%08" PF " ", B.words[i]);
            if ((i + 1) % 8 == 0)
                printf("\n"); 
        }
    }

    fclose(f);  
    // print total number of bits read. 
    printf("Total bits read: %ld.\n", nobits);

    return 0;
}