#include<stdio.h>
#include<inttypes.h>

#define BYTE uint8_t

void bin_print(BYTE i)
{
  // Number of bits in an unsigned integer
  int j = sizeof(BYTE) * 8;

  int k;

  for (j--; j >= 0; j--) {
    k = ((1 << j) & i) ? 1 : 0;
    printf("%d", k);
  }
}

int main(int argc, char *argv[])
{
    BYTE b;
    FILE *f;
    f = fopen(argv[1], "r");

    size_t nobytes;

    nobytes = fread(&b, 1, 1, f);
    while(nobytes) {
        bin_print(b);
        nobytes = fread(&b, 1, 1, f);
    }

    fclose(f);  
    printf("\n");

    return 0;
}