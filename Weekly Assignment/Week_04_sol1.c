// Level 2
#include<stdio.h> 
#include<math.h>
int main(){
    float x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, xbar, sd;
    // input
    printf("Find (sample) standard devision, please input ten Numbers only.\n\n");
    for(int c = 1; c <= 10; c++) {
        printf("input data %d : ", c);
        switch (c) {
            case 1: scanf("%f", &x1);break;
            case 2: scanf("%f", &x2);break; 
            case 3: scanf("%f", &x3);break; 
            case 4: scanf("%f", &x4);break; 
            case 5: scanf("%f", &x5);break; 
            case 6: scanf("%f", &x6);break; 
            case 7: scanf("%f", &x7);break; 
            case 8: scanf("%f", &x8);break; 
            case 9: scanf("%f", &x9);break; 
            case 10: scanf("%f", &x10); break; 
        default: break;
        }
    }

    // find SD
    xbar = (x1 + x2 + x3 + x4 + x5 + x6 + x7 + x8 + x9 + x10)/10.0;
    float sum_x = 0;
    for(int c = 1; c <= 10; c++) {
        float diff = 0;
        switch (c) {
            case 1: diff = x1-xbar; break;
            case 2: diff = x2-xbar; break;
            case 3: diff = x3-xbar; break;
            case 4: diff = x4-xbar; break;
            case 5: diff = x5-xbar; break;
            case 6: diff = x6-xbar; break;
            case 7: diff = x7-xbar; break;
            case 8: diff = x8-xbar; break;
            case 9: diff = x9-xbar; break;
            case 10: diff = x10-xbar; break;
        default: break;
        }
        sum_x += pow(diff, 2); 
    }
    
    // output
    sd = sqrt(sum_x/(10-1));
    printf("\nSample standard devision = %f", sd);

    return 0;
}
