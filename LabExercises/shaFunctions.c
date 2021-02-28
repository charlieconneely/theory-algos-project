#include<stdio.h>
#include<inttypes.h>

/* Section 2.2.2
Bitwise XOR in C: ^
Bitwise AND: &
Complement Operator: ~
Left-Shift Operator: <<
Right-Shift Operator: >>
Bitwise OR: |
*/ 

/* 
ROTR - Circular Right Shift shift all entries of a tuple to the right, (element at end goes to start)
ROTRn(x)=(x >> n) v (x << w - n)

Equivalent in C: (x >> n) | (x << w - n)

x is a w-bit word
n is an integer with 0 <= n < w
*/

// Preprocessor - replace WORD with uint32_t
#define WORD uint32_t
#define PF PRIX32

WORD SHR(WORD x, int n, int w) {
    return x >> n;
}

WORD ROTR(WORD x, int n, int w) {
    return (x >> n) | x << (w - n);
}

WORD Ch(WORD x, WORD y, WORD z) {
    return (x&y)^(~x&z);
}

WORD Maj(WORD x, WORD y, WORD z) {
    return (x&y)^(x&z)^(y&z);
}

int main(int argc, char *argv[]) {
    
    WORD x = 0xf0f0f0f0;
    WORD y = 0x0f0f0f0f;
    WORD z = 0xf0f0f0f0;

    WORD ch_ans = Ch(x, y, z);
    WORD maj_ans = Maj(x, y, z);
    WORD shr_ans = SHR(x, 10, 32);
    WORD rotr_ans = ROTR(x, 10, 32);

    printf("Ch(%08" PF ",%08" PF ",%08" PF ")=%08" PF "\n", x, y, z, ch_ans);
    printf("Maj(%08" PF ",%08" PF ",%08" PF ")=%08" PF "\n", x, y, z, maj_ans);
    printf("SHR(%08" PF ",10,32)=%08" PF "\n", x, shr_ans);
    printf("ROTR(%08" PF ",10,32)=%08" PF "\n", x, rotr_ans);
    
    return 0;
}