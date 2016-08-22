/*
Author: Luiz
3 Different approaches on two NxN matrices multiplication.
a) The naive way
b) With cache optimization by transposing the second matrix
c) With multiple threads and transposing the second matrix
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printMatrix(double *m, int n){
    //printf("Printing matrix...\n");
    int i, j;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            printf(" %.0f ", m[i*n+j]);
        }
        printf("\n");
    }
    //printf("Done printing!\n");
}

void initMatrix(double *m, int n){
    //printf("Initiating matrix...");
    int i, j;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            m[i*n+j] = j;
        }
    }
    //printf("Done\n");
}

double* transpose(double *m, int n){
    int i, j;
    double *a;
    a = malloc(n * n * sizeof(double));

    #pragma omp parallel for private(j)
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            a[i*n+j] = m[j*n+i];
        }
    }
    return a;
}

void multiplyMatrixTransposeMulti(double *c, double *a, double *b, int n){
    b = transpose(b,n);
    #pragma omp parallel
    {
        int i, j, k;
        #pragma omp for
        for(i=0; i<n; i++){
            for(j=0; j<n; j++){
                double sum = 0;
                for(k=0; k<n; k++){
                    sum = sum + a[i*n+k] * b[j*n+k];
                }
                c[i*n+j] = sum;
            }
        }
    }
}

void multiplyMatrixTransposeSingle(double *c, double *a, double *b, int n){
    int i, j, k;
    b = transpose(b,n);
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            double sum = 0;
            for(k=0; k<n; k++){
                sum = sum + a[i*n+k] * b[j*n+k];
            }
            c[i*n+j] = sum;
        }
    }
}

void multiplyMatrix(double *c, double *a, double *b, int n){
    int i, j, k;
    double sum;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            sum = 0;
            for(k=0; k<n; k++){
                sum = sum + a[i*n+k] * b[n*k+j];
            }
            c[i*n+j] = sum;
        }
    }
}

void main(int argc, char **argv){
    int n;
    double *a, *b, *c, i;
    clock_t start, end;
    float secs;
    n = atoi(argv[1]);
    a = malloc(n * n * sizeof(double));
    b = malloc(n * n * sizeof(double));
    c = malloc(n * n * sizeof(double));
    initMatrix(a,n);
    initMatrix(b,n);
    start = clock();
    multiplyMatrix(c,a,b,n);
    end = clock();
    secs = (end-start) / (double)CLOCKS_PER_SEC;
    printf("It took %.2f seconds to multiply the two matrices without transposing!\n", secs);
    //printMatrix(c,n);
    start = clock();
    multiplyMatrixTransposeSingle(c,a,b,n);
    end = clock();
    secs = (end-start) / (double) CLOCKS_PER_SEC;
    printf("It took %.2f seconds to multiply the two matrices transposing with 1 thread!\n", secs);
    //printMatrix(c,n);
    start = clock();
    multiplyMatrixTransposeMulti(c,a,b,n);
    end = clock();
    secs = (end-start) / (double) CLOCKS_PER_SEC / 4; //It should divide by number of threads, sorry!
    printf("It took %.2f seconds to multiply the two matrices transposing with multiple threads!\n", secs);
    //printMatrix(c,n);
}
