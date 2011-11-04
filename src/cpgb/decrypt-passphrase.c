#include<stdio.h>
#include<stdlib.h>
#include<termios.h>
#include<string.h>
#include<err.h>
#include "pdkdf.h"
#include "slurp.h"
#include "crypto_secretbox.h"

unsigned long long get_line(char **where, unsigned long long *leng, FILE *src){
  char *line; /*needs error handling*/
  size_t length; /*also needs to be right, which should be checked carefully*/
  line=fgetln(src, &length);
  *where=realloc(*where, length+1);
  memcpy(*where, line, length);
  (*where)[length]='\0';
  *leng=length;
} //This should live in its own file to ensure future compatibility/changing
//Oh well, always more to do.
int main(int argc, char *argv[]){
  unsigned char salt[16];
  unsigned long long saltlen =16;
  unsigned char key[crypto_secretbox_KEYBYTES];
  unsigned char *cryptdat;
  unsigned long long cryptlen;
  unsigned char nonce[crypto_secretbox_NONCEBYTES];
  unsigned char *plaindat;
  unsigned long long plainlen;
  unsigned char *password;
  unsigned long long passlen=16;
  struct termios old;
  struct termios new;
  FILE *input;
  FILE *output;
  password=malloc(passlen);
  if(password==NULL)
    err(1, "Malloc failed\n");
  if(argc !=3)
    err(1, "Usage: decrypt-passphrase encrypted output\n");
  input=fopen(argv[1], "r");
  if(input==NULL)
    err(1, "Error opening file %s", argv[1]);
  fread(salt, sizeof(char), saltlen, input);
  fread(nonce, sizeof(char), crypto_secretbox_NONCEBYTES, input);
  //We have now gotten everything we need to ask for the passphrase and
  //use it to derive the key.
  if(tcgetattr(0,&old))
    err(1, "Terminal setting ungettable\n");
  new=old;
  new.c_lflag&=~(ECHO);
  if(tcsetattr(0, TCSANOW,&new))
    err(1, "Terminal not obeying orders\n");
  printf("Enter Password:");
  fflush(stdout);
  get_line(&password, &passlen, stdin); 
  if(tcsetattr(0, TCSANOW, &old))
    err(1, "Terminal not obeying orders.\n");
  printf("\n"); //Newline nice.
  pdkdf(key, crypto_secretbox_KEYBYTES, password, passlen,
   salt, saltlen);
  //can now read in rest of file.
  cryptdat=slurp(crypto_secretbox_BOXZEROBYTES, &cryptlen, input);
  plaindat=malloc(cryptlen);
  if(crypto_secretbox_open(plaindat, cryptdat, cryptlen,nonce,key))
    err(1, "Decryption failed");
  plainlen=cryptlen-crypto_secretbox_ZEROBYTES;
  output=fopen(argv[2], "w");
  if(output==NULL)
    err(1, "Error opening %s", argv[2]);
  fwrite(plaindat+crypto_secretbox_ZEROBYTES, sizeof(char), plainlen, output);
  fclose(output);
  fclose(input);
  free(plaindat);
  free(cryptdat);
  free(password);
  exit(1);
}
