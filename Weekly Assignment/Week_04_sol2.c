// Level 2
#include<stdio.h> 
#include<math.h>
int i = 0;
int main(){
    int n = 10, c;
    float x[10], sum_x , xbar, sd, diff, diffSqa, sum_diffSqa;
   
    printf("Find (sample) standard devision., please input ten Numbers only.\n\n");
    for (c = 1; c <= n; c++){
         //input
        printf("input data %d : ", c);
        scanf("%f", &x[c]);
        // Find SD
        xbar += x[c]/n*1.0;
        sum_x += x[c];
        if (c == n){
            for (c = 1; c < n; c++){
                sum_diffSqa += (x[c] - xbar)*(x[c] - xbar);
            }
        }
    }
    // output
    sd = sqrt(sum_diffSqa/(n-1));
    printf("\nSample standard devision = %f", sd);

    return 0;
}
