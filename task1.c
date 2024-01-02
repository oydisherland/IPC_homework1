#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void printArray(float* array, int size){
    int i;
    for(i = 0; i < size; i++){
        printf(" %f ", array[i]);
    }
    printf("\n");
}

int isAdditionCorrect(float* A, float*B, float* C, int size){
    int i;
    int iterations = size;
    int mistakes = 0;
    for(i = 0; i < iterations; i++){
        int num = rand()%size;
        float correctCalculation = A[num] + B[num];
        if(C[num] != correctCalculation){
            printf("NOT CORRECT, %f should be %f", C[num], correctCalculation);
            mistakes ++;
        }
    }
    return mistakes;
}

#define NUM_REPS 100

unsigned long routine1(int n, float* A, float* B, float* C){ 
    int i; 

    //INITIALISE MATRICES
    for (i = 0; i < n; i++){
        float r1 = (float)(rand()%20); 
        float r2 = (float)(rand()%20);
        A[i] = r1;
        B[i] = r2;
    }

    // CALCULATION
    int rep;
    struct timespec ta, tb;
    clock_gettime(CLOCK_REALTIME, &ta);
    for (rep=0; rep<NUM_REPS; rep++){
        
        for (i = 0; i < n; i++){
            C[i] = A[i] + B[i];
        }

    }
    clock_gettime(CLOCK_REALTIME, &tb);

//UNNOCOMENT THE TWO LINES UNDER TO PRINT RESULTS
    //printArray(A, n); printArray(B, n); printArray(C,n);
    isAdditionCorrect(A,B,C,n);
    
    unsigned long billion = 1000000000;
    return (billion * (tb.tv_sec - ta.tv_sec) + tb.tv_nsec - ta.tv_nsec)/ NUM_REPS;
}


int main(){
    srand(time(NULL));
    int i;

    int arraySizes[10] = {pow(2,4), pow(2,6), pow(2,8), pow(2,10), pow(2,12), pow(2,14), pow(2,16), pow(2,18), pow(2,20), pow(2,22)};
    unsigned long timesRoutine1[10];


    // INITIALISE MATRICES
    float* A = (float*)malloc(pow(2,22)*sizeof(float));
    float* B = (float*)malloc(pow(2,22)*sizeof(float));
    float* C = (float*)malloc(pow(2,22)*sizeof(float));

    unsigned long test = routine1(4,A,B,C);
//GENERATE RESULTS
/*
    for ( i = 0; i < 10; i++){
        timesRoutine1[i] = routine1(arraySizes[i], A, B, C);
        printf("%lu ns\n", timesRoutine1[i]);
    }
*/
    timesRoutine1[0] = routine1(pow(2,22), A, B, C);
    printf("%lu ns\n", timesRoutine1[0]);  
    free(A);
    free(B);
    free(C);

    printf("___\n");
}