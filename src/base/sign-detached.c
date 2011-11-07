#include<stdio.h>
#include<stdlib.h>
#include "crypto_sign.h"
#include "crypto_hash.h"
#include "slurp.h"
/*Usage: sign-detached priv file
  Outputs a detached signature, sutible for checking with
  verify-detached
*/
int main(int argc, char *argv[]){
  unsigned char hash[crypto_hash_BYTES];
  unsigned char *message;
  unsigned char sighash[crypto_hash_BYTES+crypto_sign_BYTES];
  unsigned long long mlength;
  unsigned long long siglength;
  unsigned char sk[crypto_sign_SECRETKEYBYTES];
  FILE *skfile;
  FILE *mfile;
  if(argc !=3){
    fprintf(stderr, "Usage: sign-detached priv file\n");
    exit(1);
  }
  skfile=fopen(argv[1], "r");
  if(skfile==NULL){
    fprintf(stderr, "Failure to open file %s\n", argv[1]);
    exit(1);
  }
  if(fread(sk, sizeof(char), crypto_sign_SECRETKEYBYTES, skfile)!=
     crypto_sign_SECRETKEYBYTES){
    fprintf(stderr, "Reading Error\n");
    exit(1);
  }
  mfile=fopen(argv[2], "r");
  if(mfile==NULL){
    fprintf(stderr,"Unable to open file %s\n", argv[2]);
    exit(1);
  }
  message=slurp(0, &mlength, mfile);
  /*Now, why do we hash then sign? There are a few reasons:
    while we could find the section that is the signature, that would
    involve thinking hard about internals and make this less likely to work
    with different signature methods.
    Also, some signatures might use message recovery, which that approach
    would interfer with. Its just a bit more robust to changes.
  */
  if(message ==NULL){fprintf(stderr, "Read error\n"); exit(1);}
  crypto_hash(hash, message, mlength);
  crypto_sign(sighash, &siglength, hash, crypto_hash_BYTES, sk);
  if(fwrite(sighash, sizeof(char), siglength, stdout)!=siglength){
    fprintf(stderr, "Write failure\n");
    exit(1);
  }
  fclose(skfile);
  fclose(mfile);
  free(message);
  exit(0);
}
  
  
