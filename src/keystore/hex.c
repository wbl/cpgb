/*By Watson Ladd*
 *Reads standard input and outputs it in hex form*/
#include<stdio.h>
#include<stdlib.h>
int main(){
  int c;
  while((c=getchar())!=EOF){
    printf("%02x", c);
  }
  exit(0);
}
