#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "crypto_hash.h"
#include "crypto_sign.h"
#include "slurp.h"
/*Usage: verify-detached pubkey message detached
  We are permitted to take variable time: this is all public data.
  But to somplify our thinking we will do this the usual read
  then compute order.*/
int main(int argc, char *argv[]){
  unsigned char pk[crypto_sign_PUBLICKEYBYTES];
  unsigned char mhash[crypto_hash_BYTES];
  unsigned char *sighash;
  unsigned char *sigstring;
  unsigned char *message;
  unsigned long long mlength;
  unsigned long long siglength;
  unsigned long long hashlength;
  FILE *pkfile;
  FILE *sigfile;
  FILE *mfile;
  if(argc != 4){
    fprintf(stderr, "Usage: verify-detached public message sig\n");
    exit(1);
  }
  pkfile=fopen(argv[1], "r");
  mfile=fopen(argv[2], "r");
  sigfile=fopen(argv[3],"r");
  if(pkfile==NULL){
    fprintf(stderr, "Erorr opening %s\n", argv[1]);
    exit(1);
  }
  if(mfile==NULL){
    fprintf(stderr, "Error opening %s\n", argv[2]);
    exit(1);
  }
  if(sigfile==NULL){
    fprintf(stderr, "Error opening %s\n", argv[3]);
    exit(1);
  }
  message=slurp(0, &mlength, mfile);
  sigstring=slurp(0, &siglength, sigfile);
  if(fread(pk, sizeof(char), crypto_sign_PUBLICKEYBYTES, pkfile)
     != crypto_sign_PUBLICKEYBYTES){
    fprintf(stderr, "Read Error\n");
    exit(1);
  }
  if(message == NULL || sigstring==NULL){ fprintf(stderr, "Read Error\n");
    exit(1);
  }
  crypto_hash(mhash, message, mlength);
  sighash=malloc(siglength); //need to check some lengths
  if(sighash==NULL) exit(1);
  if(crypto_sign_open(sighash, &hashlength, sigstring, siglength, pk)){
    printf("Verification Failed!\n");
    exit(1);
  }
  if(hashlength != crypto_hash_BYTES){
    printf("Verification Failed!\n");
    exit(1);
  }
  if(memcmp(sighash, mhash, crypto_hash_BYTES)){
    printf("Verification Failed!\n");
    exit(1);
  }
  printf("Verification Succeeded!\n");
  exit(0);
}
