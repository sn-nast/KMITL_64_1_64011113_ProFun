// Level 2
#include<stdio.h> 
#include<math.h>
int i = 0;
int main(){
    int n = 10, c;
    float x[10], sum_x , xbar, sd, diff, diffSqa, sum_diffSqa;
   
    printf("Find (sample) standard devision., please enter ten Numbers only.\n\n");
    for (c = 0; c < n; c++){
    //input
        printf("Enter data %d : ", c+1);
        scanf("%f", &x[c]);
    // Find SD
        xbar += x[c]/n*1.0;
    }
    for (c = 0; c < n; c++){
        sum_diffSqa += pow(x[c] - xbar, 2);
    }
    sd = sqrt(sum_diffSqa/(n-1));
   
    // output
    printf("\nSample standard devision = %f", sd);

    return 0;
}
