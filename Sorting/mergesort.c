/*
Author: Luiz
Basic merge sort implementation, use it as needed
Average time complexity: O(n log n)
*/

#include <stdio.h>
#include <stdlib.h>

void merge(int *array, int begin, int middle, int end, int *workArray){
    int i = begin, j = middle, k;
    for(k=begin; k<end; k++){
        if(i < middle && (j >= end || array[i] <= array[j])){
            workArray[k] = array[i];
            i++;
        }else{
            workArray[k] = array[j];
            j++;
        }
    }
}

void copyArray(int *workArray, int begin, int end, int *array){
    int i;
    for(i=begin; i<end; i++){
        array[i] = workArray[i];
    }
}

void split(int *array, int begin, int end, int *workArray){
    int middle;
    if(end - begin < 2){
        return; //If size = 1, it's sorted
    }
    middle = (begin + end) / 2;
    split(array, begin, middle, workArray);
    split(array, middle, end, workArray);
    merge(array, begin, middle, end, workArray);
    copyArray(workArray, begin, end, array);
}

void mergesort(int *array, int size){
    int * workArray = malloc(sizeof(int) * size);
    split(array, 0, size, workArray);
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
    mergesort(array, size);
    printArray(array, size);
}
