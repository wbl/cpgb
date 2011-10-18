#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<stdio.h>
#include "crypto_box.h"
#include "randombytes.h"
/*The format of an encrypted message is as follows:
  It begins with 24 byte nonce. This nonce is currently formed as an 8 byte
  second resolution timestamp, followed by 16 random bytes.
  The remainder of file is a crypto_box.
  This is enough randomness to ensure that a collision is unlikely. 2^32
  messages can be sent in a second and the probability of collision will be
  2^-64. 2^32 messages per second can be sent for 2^64 seconds before expecting
  a single collision in the nonces. By comparison the Universe is only 2^58
  seconds old.
  Usage: encrypt public private tobesent
  Output is on stdout. Todo: make into filter, add pasphrase support (requires
  changing key generation), add large file support and blocking.
*/
int main(int argc, char *argv[]){
  FILE *pkin;
  FILE *skin;
  unsigned char pk[crypto_box_PUBLICKEYBYTES];
  unsigned char sk[crypto_box_SECRETKEYBYTES];
  FILE *datafile;
  unsigned char *data;
  unsigned char *cryptdata;
  unsigned char nonce [crypto_box_NONCEBYTES];
  unsigned long long datalength;
  int timesize;
  int i;
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
  /*Here be dragons (read assumptions)
    We have to make our nonce. Now, randombytes is a wonderful thing.
    But we want to make our nonces depend on time. How big is time_t?
    How can we turn it into bytes in an endian-independent way?
  */
  time_t now = time(NULL);
  if(sizeof(time_t)==8){ //long long
    timesize=8;
    unsigned long long noncepart;
    noncepart = (unsigned long long) now;
    for(i=0; i<8; i++){
      nonce[7-i]=noncepart % 256;
      noncepart /= 256;
    }
  }else { //its a smaller timesize
    timesize=4;
    unsigned int noncepart;
    noncepart=(unsigned int) now;
    for(i=0; i<4; i++){
      nonce[4-i]=noncepart % 256;
      noncepart /= 256;
    }
  }
  /*now we need to fill the rest */
  randombytes(nonce+timesize, crypto_box_NONCEBYTES-timesize);
  /*We have a nonce*/
  datafile=fopen(argv[3], "r");
  if(datafile==NULL){
    fprintf(stderr, "Error opening file %s", argv[3]);
    exit(1);
  }
  //Todo: add error checking on all these functions
  fseek(datafile, 0, SEEK_END);
  datalength=ftell(datafile);
  fseek(datafile, 0, SEEK_SET);
  data = malloc(datalength+crypto_box_ZEROBYTES); //Need space for padding
  if(data != NULL){
    fprintf(stderr, "Error: out of memory\n");
    exit(1);
  }
  cryptdata = malloc(datalength+crypto_box_ZEROBYTES); //this is due to the API
  if(cryptdata!=NULL){
    fprintf(stderr, "Error: out of memory\n");
    exit(1);
  }
  fread(data+crypto_box_ZEROBYTES, sizeof(char), datalength, datafile);
  crypto_box(cryptdata, data, datalength+crypto_box_ZEROBYTES, nonce, pk, sk);
  //Now to write data out
  //First the nonce
  fwrite(nonce, sizeof(char), crypto_box_NONCEBYTES, stdout);
  //And now our encrypted data.
  fwrite(cryptdata+crypto_box_BOXZEROBYTES, sizeof(char), datalength+
         crypto_box_ZEROBYTES-crypto_box_BOXZEROBYTES, stdout);
  fclose(datafile);
  free(data);
  free(cryptdata);
  exit(0);
}

  
