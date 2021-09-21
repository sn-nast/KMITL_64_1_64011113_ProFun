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

void func4(int *x){
	*x += 10 ;
}

int main() {
	int ma = 20, mb = 30;
	int x2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int *y2 = x2;
	for(int c = 0; c < 10; c++){
		func4(&*(y2 + c));
		printf("%d ", *(y2 + c));
	}
    // func2(&gx, &ma);            // Test case
	// printf("%d %d %d %d\n", ma, mb,gx,gy);
    //  func3(&mb, gx);
	//  printf("%d %d %d %d\n", ma, mb,gx,gy);

	return 0;
}