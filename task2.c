#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


void checkIfCorrect(int** matrix, int** returnmatrix, int b, int p){
    int i, j;
    int randomBlockNumberX = rand()%p;
    int randomBlockNumberY = rand()%p;
    int mistakes = 0;

    for(i = 0; i < b; i++){
        for(j = 0; j < b; j++){
            int correctValue = matrix[b*randomBlockNumberX + i][b*randomBlockNumberY + j];
            int calculatedValue = returnmatrix[b*(p-1-randomBlockNumberX) + i][b*(p-1-randomBlockNumberY) + j];
            if(correctValue != calculatedValue){
                mistakes ++;
            }
        }
    }
    if(mistakes != 0){
        printf("CALCULATIONS NOT CORRECT! FOUND %d MISTAKES\n", mistakes);
    }
}

void printMatrix(int size, int** m) {
    int i, j;
    int row = size; int col = size;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

#define NUM_REPS 100

unsigned long routine1(int n, int b, int** matrix, int** reverseMatrix){

    int i, j;
    /*
    The n*n matix is divided into blocks of the size b. These blocks make a p*p matrix.
    P is the number of rows/colums of blocks in the new matrix. 
    Number of blocks is the number of elements in the p*p matrix. 
    */
    int p = n/b;
    int numberOfBlocks = p*p; 
    
    // CALCULATIONS
    int rep;
    struct timespec ta, tb;
    clock_gettime(CLOCK_REALTIME, &ta);
    for(rep = 0; rep < NUM_REPS; rep++){

        int blocknumber;
        for(blocknumber = 0; blocknumber < numberOfBlocks; blocknumber++){
            for (i = 0; i < b; i++){
                for (j = 0; j < b; j++){

                    int blocknumberReverse = numberOfBlocks - (blocknumber + 1);
                    int copyValue = matrix[j + b*(blocknumber/p)][i + b*(blocknumber%p)];
                    reverseMatrix[j + b*(blocknumberReverse/p)][i + b*(blocknumberReverse%p)] = copyValue;
                }
            }
        } 

    }
    clock_gettime(CLOCK_REALTIME, &tb);

// PRINTING RESULTS
    /*
    printMatrix(n,matrix);
    printf("\n After operations \n");
    printMatrix(n, reverseMatrix);
    printf("\nTime used: %12.4g \n", (t2-t1)/1000000.0);
    */

    checkIfCorrect(matrix, reverseMatrix, b, p);

    unsigned long billion = 1000000000;
    return (billion * (tb.tv_sec - ta.tv_sec) + tb.tv_nsec - ta.tv_nsec)/NUM_REPS;
}


int main(){
    int i,j;
    srand(time(NULL));
    int matrixSize = pow(2,12);

// INITIALIZE MATRICES
    int** matrix; 
    int** reverseMatrix;

    // Allocate vectors with row pointers 
    matrix = (int**)calloc(matrixSize, sizeof(int*));
    reverseMatrix = (int**)calloc(matrixSize, sizeof(int*));

    // Allocate actual matrix data  
    int *matrixData = (int*)calloc(matrixSize * matrixSize, sizeof(int));
    int *reverseMatrixData = (int*)calloc(matrixSize * matrixSize, sizeof(int));
    for (i = 0; i < matrixSize; i++)
    {
        matrix[i] = matrixData + i * matrixSize;
        reverseMatrix[i] = matrixData + i * matrixSize;
    }
    // Fill matrix
    for (i = 0; i < matrixSize; i++){
        for (j = 0; j < matrixSize; j++){
            int randomA = rand()%10;
            matrix[i][j] = randomA;
        }
    }

//GENERATE RESULTS
    int blockSizes[4] = {pow(2,2), pow(2,4), pow(2,6), pow(2,8)};
    unsigned long timesRoutine1[4];

    for (i = 0; i < 4; i++){
        timesRoutine1[i] = routine1(matrixSize, blockSizes[i], matrix, reverseMatrix)/1000.0;
        printf("%lu us\n", timesRoutine1[i]);
    }

//FREE MATRICES

    free(matrix);
    free(reverseMatrix);
    free(matrixData);
    free(reverseMatrixData);

    printf("____\n");
}