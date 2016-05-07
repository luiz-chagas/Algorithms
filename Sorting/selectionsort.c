/*
Author: Luiz
Basic selection sort implementation, use it as needed
Average time complexity: O(n^2)
*/

#include <stdio.h>
#include <stdlib.h>

void selectionsort(int *array, int size){
    int i, j, min, swap;
    for(j=0; j<size; j++){
        min = j;
        for(i=j+1; i<size; i++){
            if(array[i] < array[min]){
                min = i;
            }
        }
        if(j != min){
            swap = array[j];
            array[j] = array[min];
            array[min] = swap;
        }
    }
}

void printArray(int *array, int size){
    printf("Your array: [");
    int i;
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
    selectionsort(array, size);
    printArray(array, size);
}
