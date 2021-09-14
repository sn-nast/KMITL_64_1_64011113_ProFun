#include<stdio.h>
int gx = 100, gy = 200;

void func1(int x, int y) {
	x = x + 10;	y = y + 20; gx = gx - 1; gy = gy + 1;
}

void func2(int *x,int *y) {
	*x = *x + 10; *y = *y + 20; gx = gx - 5, gy = gy + 5;
}

void func3(int* x, int y) {
	*x = *x + 30; y = y + 20;  gx = gx + 10, gy = gy - 10;
}

int main() {
	int ma = 20, mb = 30;
    // func2(&gx, &ma);            // Test case
	// printf("%d %d %d %d\n", ma, mb,gx,gy);
     func3(&mb, gx);
	 printf("%d %d %d %d\n", ma, mb,gx,gy);

	return 0;
}