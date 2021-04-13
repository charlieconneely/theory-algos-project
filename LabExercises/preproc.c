#include<stdio.h>
#include<inttypes.h>

#define BYTE uint8_t
#define WORD uint32_t
#define W 32
#define PF PRIX32

union Block {
    BYTE bytes[64];
    WORD words[16];
    int64_t sixf[8];
};

enum Status {
    READ, PAD, END
};

// get the next block
int nextBlock(FILE *f, union Block *B, enum Status *S, uint64_t *nobits) {
    size_t nobytes;

    if (*S == END) {
        return 0;
    } else if (*S == READ) {
        // try to read 64 bytes 
        nobytes = fread(B->bytes, 1, 64, f);
        // calculate the total bits read so far 
        *nobits = *nobits + (8 * nobytes);
        if (nobytes == 64) {
            return 1;
        } 
        // Enough room for padding
        else if (nobytes <= 55) {
            // append a 1 bit (and seven 0 bits to make a full byte)
            B->bytes[nobytes++] = 0x80; // in bits: 10000000
            // append enough 0 bits, leaving 64 at the end 
            while (nobytes++ < 56) {
                B->bytes[nobytes] = 0x00; // in bits: 00000000
            }   
            // Check big endian

            // Append length of original input
            B->sixf[7] = *nobits;
            // Say this is the last block
            *S = END;
        } else {
            // Gotten to the end of the input message.
            // Not enough room in this block for all the padding.
            // Append a 1 bit (and seven 0 bits to make a full byte.)
            B->bytes[nobytes] = 0x80;
            // Append 0 bits. 
            while (nobytes++ < 64) {
                B->bytes[nobytes] = 0x00; // in bits: 00000000
            }  
            // Change the status to PAD.
            *S = PAD;
        }
    } else if (*S == PAD) {
        nobytes = 0;
        // Append 0 bits. 
        while (nobytes++ < 56) {
            B->bytes[nobytes] = 0x00; // in bits: 00000000
        }  
        // Append nobits as an integer
        B->sixf[7] = *nobits;
        // Change the status to PAD.
        *S = END;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    union Block B;
    // Total number of bits read
    uint64_t nobits = 0;
    // Current status of reading input
    enum Status S = READ;
    // File pointer for reading
    FILE *f;
    // Open file from cmd line for reading
    f = fopen(argv[1], "r");
    // Number of bytes read
    size_t nobytes;

    // loop through the (preprocessed) blocks from input 
    while(nextBlock(f, &B, &S, &nobits)) {
        // print the 16 32-bit words.
        for (int i = 0; i < 16; i++)
        {
            printf("%08" PF " ", B.words[i]);
        }
        printf("\n");
    }

    fclose(f);
    // print total number of bits read.
    printf("Total bits read: %ld.\n", nobits);

    return 0;
}
