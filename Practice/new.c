#include <stdlib.h>
#include<stdio.h>


int main(void){
    int n;
    scanf("%d",&n);

  int result = 0;
  
  for (int i = 0; i < n/3; i++) {
    result += 1;
  }
  
  for (int j = 2*n/3; j < 3*n; j += 3) {
    result += 2;
  }
  int sum = result;
    printf("%d",sum );
}