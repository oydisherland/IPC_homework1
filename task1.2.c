#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

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
    if(mistakes == 0){
        printf("CORRECT\n");
    }
    return mistakes;
}

double routine1(int n, float* A, float* B, float* C){
    clock_t t1,t2;
    double w1, w2;
    int i;

    for (i = 0; i < n; i++){
        float r1 = (float)(rand()%20); 
        float r2 = (float)(rand()%20);
        A[i] = r1;
        B[i] = r2;
    }


    // SEQUENTIAL CODE - routine1:
    struct timespec ta, tb;
    clock_gettime(CLOCK_REALTIME, &ta);
    t1=clock();
    w1 = omp_get_wtime();
    for (i = 0; i < n; i++){
        C[i] = A[i] + B[i];
    }
    w2 = omp_get_wtime();
    t2=clock();
    clock_gettime(CLOCK_REALTIME, &tb);

//UNNOCOMENT THE TWO LINES UNDER TO PRINT RESULTS
    //printArray(A, n); printArray(B, n); printArray(C,n);
    //isAdditionCorrect(A,B,C,n);
    //printf("\nTime used: %12.4g \n", (t2-t1)/1000000.0);
    
    unsigned long billion = 1000000000;
    //return billion * (tb.tv_sec - ta.tv_sec) + tb.tv_nsec - ta.tv_nsec;
    return w2-w1;
}

double routine2(int n, float* A, float* B, float* C){
    clock_t t1,t2;
    double w1, w2;
    int i;

    for (i = 0; i < n; i++){
        float r1 = (float)(rand()%20); 
        float r2 = (float)(rand()%20);
        A[i] = r1;
        B[i] = r2;
    }


    // SEQUENTIAL CODE - routine1:
    struct timespec ta, tb;
    clock_gettime(CLOCK_REALTIME, &ta);
    t1=clock();
    w1 = omp_get_wtime();
    #pragma omp simd
    for (i = 0; i < n; i++){
        C[i] = A[i] + B[i];
    }
    w2 = omp_get_wtime();
    t2=clock();
    clock_gettime(CLOCK_REALTIME, &tb);

//UNNOCOMENT THE TWO LINES UNDER TO PRINT RESULTS
    //printArray(A, n); printArray(B, n); printArray(C,n);
    //isAdditionCorrect(A,B,C,n);
    //printf("\nTime used: %12.4g \n", (t2-t1)/1000000.0);
    
    unsigned long billion = 1000000000;
    return billion * (tb.tv_sec - ta.tv_sec) + tb.tv_nsec - ta.tv_nsec;
    return w2-w1;
}

int main(){
    srand(time(NULL));
    int i;

    int arraySizes[10] = {pow(2,4), pow(2,6), pow(2,8), pow(2,10), pow(2,12), pow(2,14), pow(2,16), pow(2,18), pow(2,20), pow(2,22)};
    double timesRoutine1[10];


    // INITIALISE MATRICES
    float* A = (float*)malloc(pow(2,22)*sizeof(float));
    float* B = (float*)malloc(pow(2,22)*sizeof(float));
    float* C = (float*)malloc(pow(2,22)*sizeof(float));


//GENERATE RESULTS

    for ( i = 0; i < 10; i++){
        timesRoutine1[i] = routine2(arraySizes[i], A, B, C);
        printf("%12.4g us\n", timesRoutine1[i]);
    }

    free(A);
    free(B);
    free(C);
}