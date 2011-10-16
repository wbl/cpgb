#include "crypto_sign.h"
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
  unsigned long long mlength;
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
  if(fread(sk, sizeof(char), crypto_sign_SECRETKEYBYTES, keyfile)!=crypto_sign_SECRETKEYBYTES){
    fprintf(stderr, "Error reading secret key\n");
    exit(1);
  }
  /*we should have the key in memory now.*/
  fclose(keyfile);
  filesign=fopen(argv[2], "r");
  fseek(filesign, 0, SEEK_END);
  mlength = ftell(filesign);
  fseek(filesign, 0, SEEK_SET);
  mlength -= ftell(filesign);
  memfile=malloc(mlength*sizeof(char));
  fread(memfile, sizeof(char), mlength, filesign);
  signedfile=malloc((mlength+crypto_sign_BYTES)*sizeof(char));
  crypto_sign(signedfile, &signlength, memfile, mlength, sk);
  fwrite(signedfile, sizeof(char), signlength, stdout);
  fclose(filesign);
  free(memfile);
  free(signedfile);
  exit(0);
}
