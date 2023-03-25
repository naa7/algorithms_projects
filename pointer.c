#include <stdio.h>
#include <stdlib.h>


int main() {
  int x = 5;
  int* p = &x;
  const int const *q = &x;
  printf("value of x : %d\n", x);
  printf("value of pointer p : %d\n", *p);
  printf("value of pointer q : %d\n", *q);
  x = 7;
  printf("new value of x : %d\n", x);
  printf("new value of pointer p : %d\n", *p);
  printf("new value of pointer q : %d\n", *q);
  *p = 9;
  printf("new value of x : %d\n", x);
  printf("new value of pointer p : %d\n", *p);
  printf("new value of pointer q : %d\n", *q);

  int* y = (int*)malloc(sizeof(int)); //  The malloc() function allocates memory
                                      //  and leaves the memory uninitialized.

  return 0 ;
}
