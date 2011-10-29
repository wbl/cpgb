#include<stdio.h>
#include<stdlib.h>
#include "crypto_box.h"
#include "slurp.h"
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
    fprintf(stderr, "Usage: decrypt public private tobesent\n");
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
  if(fclose(pkin)<0) exit(1); /*What else am I supposed to do?*/
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
  if(fclose(skin)<0) exit(1); /*This is sort of ridiculous. On writing I can
                                get why we might have work, but reading?*/
  //Now we have loaded our keys.
  //Time to load the file and see what we have
  cryptdat=fopen(argv[3], "r");
  if(cryptdat==NULL){
    fprintf(stderr, "Unable to open file %s", argv[3]);
    exit(1);
  }
  if(fread(nonce, sizeof(char), crypto_box_NONCEBYTES, cryptdat)!=
     crypto_box_NONCEBYTES) exit(1);
  /*What happens next is a hack. Slurp sluprs starting at the current point*/
  cryptotext = slurp(crypto_box_BOXZEROBYTES, &cryptolength, cryptdat);
  if(cryptotext==NULL) exit(1);
  plaintext = malloc(cryptolength);
  if(plaintext==NULL) exit(1);
  plaintextlength=cryptolength-crypto_box_ZEROBYTES;
  if(crypto_box_open(plaintext, cryptotext, cryptolength, nonce, pk, sk)){
    fprintf(stderr, "Cryptotext invalid\n");
    exit(3);
  }
  if(fwrite(plaintext+crypto_box_ZEROBYTES, sizeof(char),
            plaintextlength, stdout)!=plaintextlength) exit(1);
  free(plaintext);
  free(cryptotext);
  //If this fails we aren't doing anything else anway.
  fclose(cryptdat);
  exit(0);
}
