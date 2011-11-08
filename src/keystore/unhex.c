/*Convert from hex on standard input back to binary*/
#include<stdlib.h>
#include<stdio.h>
int digval(char c){
  if(c<58){ //9 is numeric and has value 57
    return c-48; //maps 0 to 0
  }else {
    return c-87; //a is ascii 97 and represents 10
  }
}

int main(){
  int c;
  int flag=0;
  int lastval;
  while((c=getchar())!=EOF){
    if(flag){ //we have read the second part
      putchar(lastval*16+digval(c));
      flag=0;
    }else{
      lastval=digval(c);
      flag=1;
    }
  }
  exit(0);
}
