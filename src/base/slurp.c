#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"slurp.h"
//slurp puts a file into memory preceeded by offset empty bytes and returns
//total allocated bytes in length.
//We might not be able to stat the file so should use other means.
//code based on that DJB wrote for sha512 checksuming
unsigned char *slurp(unsigned long long offset,
                    unsigned long long *length, FILE *source){
  int ch=0;
  unsigned long long inputlen=0;
  unsigned long long inputalloc=0;
  unsigned char *input;
  inputlen = offset;
  input = malloc(offset*sizeof(char));
  if(input == NULL) return NULL;
  while ((ch = fgetc(source)) != EOF) {
    if (inputlen >= inputalloc) {
      void *newinput;
      while (inputlen >= inputalloc)
        inputalloc = inputalloc * 2 + 1;
      if (posix_memalign(&newinput,16,inputalloc) != 0) return NULL;
      memcpy(newinput,input,inputlen);
      free(input);
      input = newinput;
    }
    input[inputlen++] = ch;
  }
  *length = inputlen;
  return input;
}
