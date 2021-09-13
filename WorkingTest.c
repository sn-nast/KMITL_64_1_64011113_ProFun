#include<stdio.h>
#include<stdlib.h>
int main(){

  int x = 10 ,y = 20 , z = 30 ,*p1 ,*p2;
  p1 = &x;
  p2 = &y;
  printf("%d %d %d %d %d\n", x, y, z, *p1, *p2);

  x = 80;
  printf("%d %d %d %d %d\n", x, y, z, *p1, *p2);

  p1 = &z;
  p2 = p1 ;
  printf("%d %d %d %d %d\n", x, y, z, *p1, *p2);

  *p1 = 100;
  printf("%d %d %d %d %d\n", x, y, z, *p1, *p2);

}
// 6684160
// 1
// 6684152
// 6684160

// 6684160
// 1
// 6684152
// 6684160