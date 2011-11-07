#include "crypto_sign.h"
#include "slurp.h"
#include <stdio.h>
#include <stdlib.h>
/*This will be run as cpgb-sign private file. It will write a signed
  version of file to standard output. The file has to fit in memory.
  Later versions will fix this.
  Later versions will also support detached signatures
  Later versions will also protect the file by requiring a passphrase.
*/
int main(int argc, char **argv){
  unsigned char sk[crypto_sign_SECRETKEYBYTES];
  FILE * keyfile;
  FILE * filesign;
  long long mlength;
  long long temp;
  unsigned char *memfile;
  unsigned char *signedfile;
  unsigned long long signlength;
  /*We begin by asking if we have enough arguments*/
  if(argc != 3){
    fprintf(stderr, "Usage: cpgb-sign private file\n");
    exit(1);
  }
  /*Okay, time to boldly go ahead*/
  keyfile=fopen(argv[1], "r");
  if(keyfile==0){
    fprintf(stderr, "Unable to open file %s\n", argv[1]);
    exit(1);
  }
  if(fread(sk, sizeof(char), crypto_sign_SECRETKEYBYTES, keyfile)
     !=crypto_sign_SECRETKEYBYTES){
    fprintf(stderr, "Error reading secret key\n");
    exit(1);
  }
  /*we should have the key in memory now.*/
  if(fclose(keyfile)<0) exit(1);
  filesign=fopen(argv[2], "r");
  if(filesign == NULL){ fprintf(stderr, "Unable to open file %s", argv[2]);
    exit(1);
  }
  memfile=slurp(0, &mlength, filesign);
  if(memfile==NULL) exit(1);
  signedfile=malloc((mlength+crypto_sign_BYTES)*sizeof(char));
  if(signedfile ==NULL){fprintf(stderr, "Out of Memory\n"); exit(1);}
  crypto_sign(signedfile, &signlength, memfile, mlength, sk);
  if(fwrite(signedfile, sizeof(char), signlength, stdout)!=signlength) exit(1);
  fclose(filesign);
  free(memfile);
  free(signedfile);
  exit(0);
}
