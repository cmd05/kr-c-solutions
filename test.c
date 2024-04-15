#include <stdio.h>

int main() {
  if(1)
    if(0)
      printf("a");
  else // this is associated with the nested if block
    printf("b");
}