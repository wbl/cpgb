#include "crypto_box.h"
#include "crypto_sign.h"
#include "randombytes.h"
#include <stdio.h>
#include <unistd.h>
/*TODO: Add passphrase for keys */
/*This is very much New Jersey: It runs*/
int main(int argc, char *argv[]){
  /*Usage: cpgb-keygen -[s|e] pubfile privfile */
  /*Pubfile will contain a public key. */
  /*Privefile will contain a private key*/
  /*Option: s creates a signing key ed25519*/
  /*Option: e creates an encryption key, curve25519 */
  /*Currently no way to distinguish keys of different type.*/
  int signing =0;
  int encrypting =0; //flags for what to do
  int opt=0; //We are using getopts, need a variable to switch on.
  int pksize=0;
  int sksize=0;
  FILE *public;
  FILE *private;
  opterr=0; //from getopts
  int optc;
  while((optc=getopt(argc, argv, "se"))!=-1)
    switch (optc) {
    case 's':
      signing = 1;
      break;
    case 'e':
      encrypting=1;
      break;
    case '?':
      fprintf(stderr, "Usage: cpgb-keygen -[se] public private\n");
      exit(1);
    }
  if(encrypting==1 && signing==1){
    fprintf(stderr, "s and e together not supported.\n");
    exit(1);
  }
  if(encrypting==0 && signing == 0){
    fprintf(stderr, "specify an option please.\n");
    exit(1);
  }

  if(argc != 4){
    fprintf(stderr, "Incorrect number of arguments\n");
    exit(1);
  }
  unsigned char * pk;
  unsigned char * sk;
  if(secret ==1){
    pk=malloc(sizeof(char)*crypto_sign_PUBLICKEYBYTES);
    sk=malloc(sizeof(char)*crypto_sign_SECRETKEYBYTES);
    if(pk==NULL || sk==NULL){
      fprintf(stderr, "Unable to allocate memory.");
      exit(1);
    }
    pksize=crypto_sign_PUBLICKEYBYTES;
    sksize=crypto_sign_SECRETKEYBYTES;
    crypto_sign_keypair(pk, sk);
  }

  if(encrypting ==1){
    pk=malloc(sizeof(char)*crypto_box_PUBLICKEYBYTES);
    sk=malloc(sizeof(char)*crypto_box_SECRETKEYBYTES);
    if(pk==NULL || sk==NULL){
      fprintf(stderr, "Unable to allocate memory.");
      exit(1);
    }
    pksize=crypto_box_PUBLICKEYBYTES;
    sksize=crypto_box_SECRETKEYBYTES;
    crypto_box_keypair(pk,sk);
  }
  //We now have to write out our keypair. I assume
  public=fopen(argv[2], "w");
  if(public ==NULL){
    fprintf("Error: cannot open %s", argv[2]);
    exit(1);
  }
  fwrite(pk, sizeof(char), pksize, public);
  fclose(public);
  private=fopen(argv[3], "w");
  if(private ==NULL){
    fprintf("Error: cannot open %s", argv[3]);
    exit(1);
  }
  fwrite(sk, sizeof(char), sksize, private);
  fclose(private);
  free(sk);
  free(pk);
  exit(0);
}
