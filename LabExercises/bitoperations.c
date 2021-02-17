#include <stdio.h>

void bin_print(unsigned int i)
{
  // Number of bits in an unsigned integer
  int j = sizeof(unsigned int) * 8;

  int k;

  for (j--; j >= 0; j--) {
    k = ((1 << j) & i) ? 1 : 0;
    printf("%d", k);
  }
}

int main(int argc, char *argv[])
{
  // set i to a literal value
  unsigned int i = 0x0f0f0f0f;

  printf("Original:\t");
  // i in binary
  bin_print(i);
  printf("\t%x\t%u\n", i, i);

  int j = sizeof(unsigned int) * 8; // 32

  for (j--; j >=0; j--) {
    // 1 shifted j times.
    bin_print(i << j); printf("\n");
    // i
    bin_print(i); printf("\n");
    printf("-------------------------------- &\n");
    // (1 shifted left j times) bitwise logical and i
    bin_print((1 << j) & i); printf("\n\n");
  }

  return 0;
}
