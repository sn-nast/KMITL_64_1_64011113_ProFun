// Activity 04
// 64011113
#include<stdio.h>

int isPrime(int);
int main() 
{
	int x;
    printf("Enter number : ");
	scanf("%d", &x);
	if (isPrime(x) == 1)
		printf("Prime number");
	else
		printf("Not Prime number");
	return 0;
}

int isPrime(int a)
{
    int i, count = 0;
    for (i = 1; i <= a; i++){
        if(a%i == 0)    {count++;}
    }
    if (count == 2) {return 1;}
	else {return 0;}
}