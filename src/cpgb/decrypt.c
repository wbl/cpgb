#include<stdio.h>
#include<stdlib.h>
#include "crypto_box.h"
/*Decryption is very similar to encryption.
We are used as follows
decrypt public private sent
sent has a 24 byte nonce (crypto_box_NONCEBYTES) followed by a crypto_box.
We have to allocate the space to unpack it and output it.
*/
int main(int argc, char * argv[]){
  FILE *pkin;
  FILE *skin;
  FILE *cryptdat;
  unsigned char nonce[crypto_box_NONCEBYTES];
  unsigned char pk[crypto_box_PUBLICKEYBYTES];
  unsigned char sk[crypto_box_SECRETKEYBYTES];
  unsigned char *cryptotext;
  unsigned char *plaintext;
  int datalength;
  long cryptolength;
  long plaintextlength;
  //First our usual. Copied from encrypt.c
  if(argc !=4){
    fprintf(stderr, "Usage: encrypt public private tobesent\n");
    exit(1);
  }
  /*we now bravely forge ahead.*/
  pkin=fopen(argv[1], "r");
  if(pkin==NULL){
    fprintf(stderr, "Unable to open file %s", argv[1]);
    exit(1);
  }
  if(fread(pk, sizeof(char), crypto_box_PUBLICKEYBYTES, pkin)!=
     crypto_box_PUBLICKEYBYTES){
    fprintf(stderr, "Unable to load public key\n");
    exit(1);
  }
  fclose(pkin);
  /*we have at this point loaded the public key*/
  skin=fopen(argv[2], "r");
  if(skin==NULL){
    fprintf(stderr, "Unable to open file %s", argv[2]);
    exit(1);
  }
  if(fread(sk, sizeof(char), crypto_box_SECRETKEYBYTES, skin)!=
     crypto_box_SECRETKEYBYTES){
    fprintf(stderr, "Unable to load secret key\n");
    exit(1);
  }
  fclose(skin);
  //Now we have loaded our keys.
  //Time to load the file and see what we have
  cryptdat=fopen(argv[3], "r");
  if(cryptdat==NULL){
    fprintf(stderr, "Unable to open file %s", argv[3]);
    exit(1);
  }
  fread(nonce, sizeof(char), crypto_box_NONCEBYTES, cryptdat);
  int postnonce = ftell(cryptdat);
  fseek(cryptdat, 0, SEEK_END);
  datalength = ftell(cryptdat)-postnonce;
  cryptotext=malloc(datalength+crypto_box_BOXZEROBYTES);
  plaintext=malloc(datalength+crypto_box_BOXZEROBYTES);
  cryptolength = datalength + crypto_box_BOXZEROBYTES;
  plaintextlength = cryptolength-crypto_box_ZEROBYTES;
  if(cryptotext==NULL || plaintext==NULL){
    fprintf(stderr, "Out of Memory!\n");
    exit(1);
  }
  fseek(cryptdat, postnonce, SEEK_SET);
  fread(cryptotext+crypto_box_BOXZEROBYTES, sizeof(char),
        datalength, cryptdat);
  if(crypto_box_open(plaintext, cryptotext, cryptolength, nonce, pk, sk)){
    fprintf(stderr, "Cryptotext invalid\n");
    exit(1);
  }
  fwrite(plaintext+crypto_box_ZEROBYTES, sizeof(char),
         plaintextlength, stdout);
  free(plaintext);
  free(cryptotext);
  fclose(cryptdat);
  exit(0);
}
