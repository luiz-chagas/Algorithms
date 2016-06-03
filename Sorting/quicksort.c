/*
Basic quicksort implementation, use as needed
Author: Luiz
*/

#include <stdio.h>
#include <stdlib.h>

int partition(int *array, int start, int end){
    int aux, j, i = start, pivot = array[end];
    for(j = start; j < end; j++){
        if(array[j] <= pivot){
            aux = array[i];
            array[i] = array[j];
            array[j] = aux;
            i++;
        }
    }
    aux = array[i];
    array[i] = array[end];
    array[end] = aux;
    return i;
}

void quicksort(int *array, int start, int end){
    int pivot;
    if(start < end){
        pivot = partition(array, start, end);
        quicksort(array,start,pivot-1);
        quicksort(array,pivot+1,end);
    }
}

void printArray(int *array, int size){
    int i;

    printf("Your array: [");
    for(i=0; i<size; i++){
        printf(" %d ", array[i]);
    }
    printf("]\n");
}

int main(int argc, char *argv[]){
    int size;
    if(argc != 2){
        printf("Usage: ./sort size\n");
        return 1;
    }
    size = atoi(argv[1]);
    int * array = malloc(sizeof(int) * size);
    //Initializing array
    int i;
    srand(time(NULL));
    for(i=0; i<size; i++){
        array[i] = rand() % (size*10); //Random numbers between 0 and size*10
    }
    printArray(array, size);
    printf("Sorting...\n");
    quicksort(array, 0, size-1);
    printArray(array, size);
}
