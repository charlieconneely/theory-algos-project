#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
  Code and notes adapted from:
  https://www.gnu.org/software/libc/manual/html_node/Getopt.html
*/
int main(int argc, char **argv)
{
  // flags used to denote which argument was passed in + stop program
  // from executing more than one option
  int aflag = 0;
  int bflag = 0;
  int hflag = 0;
  char *cvalue = NULL;
  int index;
  int c;

  // Set this var to 0 so that getopt will return a '?' if unknown arg is passed in.
  // Otherwise, getopt will detect opterr to be non-zero and print an error message.
  opterr = 0;

  // getopt will return -1 when no more arguments are present
  while((c = getopt(argc, argv, "abhc:")) != -1)
    switch(c)
      {
      case 'a':
        aflag = 1;
        break;
      case 'b':
        bflag = 1;
        break;
      case 'h':
        hflag = 1;
        break;
      case 'c':
        // optarg - option argument (set by getopt)
        cvalue = optarg;
        break;
      case '?':
        // optopt stores an unknown option character which was passed in as an argument
        if(optopt == 'c')
          fprintf(stderr, "Option -%c requires an argument.\n", optopt);
        else if(isprint(optopt))
          fprintf(stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
        return 1;
      default:
        abort();
      }

  printf("aflag = %d, bflag = %d, hvalue = %d cvalue = %s\n",
          aflag, bflag, hflag, cvalue);

  // optind - represents index of argument to be processed
  // used to determine where non-option arguments begin
  for(index = optind; index < argc; index++)
    printf("Non-option argument %s\n", argv[index]);
  return 0;
}

// int main(int argc, char *argv[]) {
//   for (int i = 0; i < argc; i++) {
//     printf("%s\n", argv[i]);
//   }
//   return 0;
// }
