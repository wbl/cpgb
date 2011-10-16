#include "crypto_sign.h"
#include <stdio.h>
#include <stdlib.h>
/*This will be run as cpgb-verify public file.
  If file is signed it will print the contents of the file to stdout.
  Else it will return a distinct error code.
*/
int main(int argc, char **argv){
  unsigned char pk[crypto_sign_PUBLICKEYBYTES];
  FILE * keyfile;
  FILE * filesign;
  unsigned long long slength;
  unsigned char *memfile;
  unsigned char *unsignedfile;
  unsigned long long mlength;
  /*We begin by asking if we have enough arguments*/
  if(argc != 3){
    fprintf(stderr, "Usage: cpgb-verify public file\n");
    exit(1);
  }
  /*Okay, time to boldly go ahead*/
  keyfile=fopen(argv[1], "r");
  if(keyfile==0){
    fprintf(stderr, "Unable to open file %s\n", argv[1]);
    exit(1);
  }
  if(fread(pk, sizeof(char), crypto_sign_PUBLICKEYBYTES, keyfile)
     !=crypto_sign_PUBLICKEYBYTES){
    fprintf(stderr, "Error reading secret key\n");
    exit(1);
  }
  /*we should have the key in memory now.*/
  fclose(keyfile);
  filesign=fopen(argv[2], "r");
  fseek(filesign, 0, SEEK_END);
  slength = ftell(filesign);
  fseek(filesign, 0, SEEK_SET);
  slength -= ftell(filesign);
  memfile=malloc(slength*sizeof(char));
  fread(memfile, sizeof(char), slength, filesign);
  unsignedfile=malloc(slength*sizeof(char));
  if(crypto_sign_open(unsignedfile, &mlength, memfile, slength, pk) !=0){
    fprintf(stderr, "Failed verification.\n");
    exit(3);
  }
  fwrite(unsignedfile, sizeof(char), mlength, stdout);
  fclose(filesign);
  free(memfile);
  free(unsignedfile);
  exit(0);
}
