#include<stdio.h>
#include<inttypes.h>

#define BYTE uint8_t
#define WORD uint32_t
#define W 32
#define PF PRIX32

// SHA256 works on blocks of 512 bits 
union Block {
    // 8 x 64 = 512 - dealing with blocks as bytes 
    BYTE bytes[64];
    // 32 x 16 = 512 - dealing with blocks as words 
    WORD words[16];
    // 64 x 8 = 512 - dealing with last 64 bits of last block
    int64_t sixf[8];
};

// For keeping track of where we are with the input message/padding
enum Status {
    READ, PAD, END
};

// Returns 1 if it created a new block from original message or padding.
// Returns 0 if all padded message has already been consumed. 
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
            // This happens when we can read 64 bytes from f
            return 1;
        } 
        // Enough room for padding
        else if (nobytes < 56) {
            // This happens when we have enough room for all the padding
            // append a 1 bit (and seven 0 bits to make a full byte)
            B->bytes[nobytes] = 0x80; // in bits: 10000000
            // append enough 0 bits, leaving 64 at the end 
            for (nobytes++; nobytes < 56; nobytes++) {
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
            for (nobytes++; nobytes < 64; nobytes++) {
                B->bytes[nobytes] = 0x00; // in bits: 00000000
            }  
            // Change the status to PAD.
            *S = PAD;
        }
    } else if (*S == PAD) {
        // Append 0 bits. 
        for (nobytes = 0; nobytes < 56; nobytes++) {
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
