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
  unsigned int i = 0xffffffff;

  printf("Original:  ");
  // i in binary
  bin_print(i);
  printf("\t%x\t%d\n", i, i);

  for (int j = 0; j < 40; j++) {
    printf("%3u << %2d: ", i, j);
    // i shifted left j times
    bin_print(i << j);
    printf("\n");
  }

  return 0;
}
