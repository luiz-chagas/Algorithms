/*
Author: Luiz
Hello World using as much threads as supported by your processor
*/

#include <stdio.h>

void main(){
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        printf("Hello world from thread %d\n", ID);
    }
}
