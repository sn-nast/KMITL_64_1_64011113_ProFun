#include<stdio.h>
int main()
{
	char str[50];
	char* ptr;
	ptr = str;
	scanf("%s", str);
	printf("str = %s\n", str);
	printf("ptr = %s\n", ptr);

	while (*ptr != '\0') ptr++;
	ptr--;
	printf("ptr = %s\n", ptr);
	printf("reverse : \n    ");
	while (ptr >= str) {
		printf("%c", *ptr);
		ptr--;
	}

	return 0;
}