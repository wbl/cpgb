#include<stdlib.h>
#include<string.h>
#include "slurp.h"
#include "crypto_hash.h"
#include "randombytes.h"
#include "crypto_stream.h"
#include "pdkdf.h"

void memxor(unsigned char *restrict dst, unsigned char *restrict scr,
            unsigned long long length){
  for(unsigned long long i=0; i<length; i++){
    *(dst+i) ^= *(scr+i);
  }
}
/*The following is a KDF based on the Scrypt paper by Colin Percival.*
 *It is very expensive to make in hardware because RAM is required.*/
/*Right now we just hash. Will fix later*/
int pdkdf(unsigned char *key,
          unsigned long long keylength,
          unsigned char *passphrase,
          unsigned long long passlength,
          unsigned char *salt,
          unsigned long long saltlength){
  unsigned char *phrase;
  unsigned char hash[crypto_hash_BYTES];
  phrase=malloc(saltlength+passlength);
  memcpy(phrase, salt, saltlength);
  memcpy(phrase+saltlength, passphrase, passlength);
  crypto_hash(hash, phrase, saltlength+passlength);
  memcpy(key, hash, keylength);
  return 0;
}

int romix(unsigned char *key,
          unsigned long long keylength,
          unsigned char *passphrase,
          unsigned long long passlength,
          unsigned char *salt,
          unsigned long long saltlength){
  /*This code will be tested and debugged sometime*/
  unsigned char *saltphrase;
  unsigned char *workspace;
  unsigned char **hashes;
  unsigned char xarray[crypto_hash_BYTES];
  unsigned char yarray[crypto_hash_BYTES];
  unsigned long long index;
  unsigned char nonce[crypto_stream_NONCEBYTES];
  int workfactor=1048576;//2^20. We are using 64 megabytes of ram.
  workspace=malloc(workfactor*crypto_hash_BYTES);
  hashes=malloc(sizeof(char *)*workfactor);
  saltphrase=malloc(saltlength+keylength);
  if(workspace ==NULL || hashes==NULL ||saltphrase==NULL) return -1; //error
  for(int i=0;i<workfactor; i++){
    hashes[i]=workspace+(i*crypto_hash_BYTES);
  }
  //We have initialized our data structures.
  memcpy(saltphrase, salt, saltlength);
  memcpy(saltphrase+saltlength, passphrase, passlength);
  crypto_hash(hashes[0], saltphrase, saltlength+passlength);
  for(int i=1; i<workfactor; i++)
    crypto_hash(hashes[i], hashes[i-1], crypto_hash_BYTES);
  //We have now filled hashes with random data.
  memcpy(xarray, hashes[workfactor-1], crypto_hash_BYTES);
  for(int i=0; i<workfactor; i++){
    index=xarray[2]*65536+xarray[1]*256+xarray[0];
    index %=workfactor;
    memxor(xarray, hashes[index], crypto_hash_BYTES);
    crypto_hash(yarray, xarray, crypto_hash_BYTES);
    memcpy(xarray, yarray, crypto_hash_BYTES);//aliasing issues.
    //While not problem today
    //who knows what implementors might do in future for speed?
  }
  //at this point xarray is our result. xarray is 64 bytes,
  //long enough to be a key for crypto_stream.
  memset(nonce, 0, crypto_stream_NONCEBYTES);
  crypto_stream(key, keylength, xarray, nonce);
  free(workspace);
  free(hashes);
  free(saltphrase);
  return 0;
}
