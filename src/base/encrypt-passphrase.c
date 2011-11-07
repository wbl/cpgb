#include<stdio.h>
#include<stdlib.h>
#include<sys/ioctl.h>
#include<termios.h>
#include<string.h>
#include "pdkdf.h"
#include "slurp.h"
#include "crypto_secretbox.h"
#include "randombytes.h"
unsigned long long get_line(char **where, unsigned long long *leng, FILE *src){
  char *line; /*needs error handling*/
  size_t length; /*also needs to be right, which should be checked carefully*/
  line=fgetln(src, &length);
  *where=realloc(*where, length+1);
  memcpy(*where, line, length);
  (*where)[length]='\0';
  *leng=length;
}
/*usage: encrypt-passphrase file dest
  encrypt-passphrase has a bit of interaction with the user to
  generate the key and nonce, then saves the encryption to dest.
  The salt and nonce used are written before dest.*/
int main(int argc, char *argv[]){
  FILE *input;
  FILE *output;
  unsigned char *inputdat;
  unsigned long long inputlen;
  unsigned char *outputdat;
  unsigned long long outputlen;
  unsigned char *password;
  unsigned long long passlength;
  unsigned char *secondpass; //need to prompt user twice
  unsigned long long secondpasslength;
  unsigned char nonce[crypto_secretbox_NONCEBYTES];
  unsigned char key[crypto_secretbox_KEYBYTES];
  unsigned char salt[16];
  unsigned long long saltlen=16; //32 would be overkill.
  if(argc !=3){ //TODO: replace with err everywhere.
    fprintf(stderr,"Usage: encrypt-passphrase input output\n");
    exit(1);
  }
  randombytes(nonce, crypto_secretbox_NONCEBYTES);
  randombytes(salt, saltlen);
  passlength=16;
  password=malloc(passlength);
  if(password==NULL) exit(1);
  secondpasslength=passlength;
  secondpass=malloc(secondpasslength);
  /*Its time to prompt the user for a password*
   *For security reasons must turn off echoing.
   We also want prompts to appear correctly*/
  struct termios old;
  struct termios new;
  do {
    if(tcgetattr(0, &old)){
      fprintf(stderr, "Unable to get tty settings\n");
      exit(1);
    }
    new=old;
    new.c_lflag &= (~ECHO);
    if(tcsetattr(0, TCSANOW, &new)){
      fprintf(stderr, "Unable to disable echo\n");
      exit(1);
    }
    printf("Enter a passphrase:");
    fflush(stdout);
    /*At this point we encounter  an issue: getline is missing!*
     *Solution: use it and define it elsewhere.*
     *Lion fixes this one.*/
    if(get_line(&password, &passlength, stdin)<0) exit(1);
    printf("\nRepeat the passphrase:");
    if(get_line(&secondpass, &secondpasslength, stdin)<0) exit(1);
    if(tcsetattr(0, TCSANOW, &old)){
      fprintf(stderr, "Unable to renable echo\n");
      exit(1);
    }
    if(passlength != secondpasslength){
      printf("\nPassphrases do not match\n");
      continue;
    }
    if(memcmp(password, secondpass, passlength)){
      printf("\nPassphrases do not match\n");
      continue;
    }
    break;
  } while(1); //Yay for C tricks.
  printf("\n"); //needed for convience.
  //We now have our password. Time to make a key
  free(secondpass);
  pdkdf(key, crypto_secretbox_KEYBYTES, password, passlength, salt, saltlen);
  //And at this point we do some very conventional things.
  input=fopen(argv[1], "r");
  if(input==NULL){
    fprintf(stderr, "Error opening file %s\n", argv[1]);
    exit(1);
  }
  inputdat=slurp(crypto_secretbox_ZEROBYTES, &inputlen, input);
  outputdat=malloc(inputlen);
  if(outputdat==NULL) exit(1);
  crypto_secretbox(outputdat, inputdat, inputlen, nonce, key);
  outputlen=inputlen-crypto_secretbox_BOXZEROBYTES;
  output=fopen(argv[2], "w");
  if(output==NULL){
    fprintf(stderr, "Error opening file %s\n",argv[2]);
    exit(1);
  }
  /*Now we write out the salt, the nonce, and the outputdata*/
  if(fwrite(salt, 1, saltlen, output)!=saltlen) exit(1);
  if(fwrite(nonce, 1, crypto_secretbox_NONCEBYTES, output)!=
     crypto_secretbox_NONCEBYTES) exit(1);
  if(fwrite(outputdat+crypto_secretbox_BOXZEROBYTES,1, outputlen, output)!=
     outputlen) exit(1);
  fclose(output);
  fclose(input);
  free(password);
  exit(0);
}

