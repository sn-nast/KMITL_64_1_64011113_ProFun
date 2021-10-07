#include<stdio.h>
#include<math.h>

int main() {
	char h[] = "1234567";
	printf("%s\n", h);
	for(int i = 0; i < 9; i++){
		printf("%c\n", h[i]);
	}
}