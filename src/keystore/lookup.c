#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*lookup store pattern*
 *searches store for pattern.*
 *pattern is key:regex*
 *prints out matching record.*
 *store is a file of records seperated by double new lines*
 *each record has lines in key:value form*
 *example: name:Bob Jones *
 *         email:bob@example.com *
 *         keytype:authorization *
 *         comment: signs my subkeys*
 *         key:<64 hex digits> *
 *keytype can be authorization, encryption, signing. Multiple keys per*
 *name and email are allowed, and comment should be used to distinguish them*
 *note that comment is user-interpreted. Be careful!*/
//to the extent we have types, use them
struct record {
  struct keyval *pairs;
};

struct keyval {
  char *key;
  char *val;
  struct keyval *next;
};

void free_keyval(struct keyval *val){
  free(val->key);
  free(val->val);
  if(val->next) free_keyval(val->next);
}

void init_keyval(struct keyval *val){
  val->key=NULL;
  val->val=NULL;
  val->next=NULL;
}

struct keyval *make_keyval(char *key; char *value; struct keval *next){
  //we copy the key and value.
  //I wish C had gc
  struct keyval *newval;
  newval=malloc(sizeof(struct keyval));
  if(newval==NULL) return NULL;
  keylen=strlen(key)+1; //null byte
  valen=strlen(value)+1; //null byte
  newval->key=malloc(keylen);
  if(newval->key==NULL){
    free(newval);
    return NULL;
  }
  newval->val=malloc(valen);
  if(newval->val==NULL){
    free(newval->key);
    free(newval);
    return NULL;
  }
  strlcpy(newval->val, value, valen);
  strlcpy(newval->key, key, keylen);
  newval->next=next;
  return newval;
}

void free_record(struct record *rec){
  if(rec->pairs) free_keyval(rec->pairs);
  free(rec);
}

struct keyval *read_keyval(FILE *input){
  //time to parse: string":"string
  
}
