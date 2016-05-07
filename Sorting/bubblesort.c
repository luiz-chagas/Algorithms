/*
Author: Luiz
Basic bubblesort implementation, use it as needed
Average time complexity: O(n^2)
*/

#include <stdio.h>
#include <stdlib.h>

void bubblesort(int *array, int size){
    int i, swap, changed = 0;
    do{
        changed = 0;
        for (i=1; i<size; i++){
            if(array[i-1] > array[i]){
                swap = array[i];
                array[i] = array[i-1];
                array[i-1] = swap;
                changed = 1;
            }
        }
    }while(changed != 0);
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
    bubblesort(array, size);
    printArray(array, size);
}
