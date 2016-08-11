#include <stdio.h>

void main(){
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        printf("Hello world from thread %d\n", ID);
    }
}
