#include <math.h> 
#include <stdio.h>

// Lab 1
//=====

// 1. In your main function, define the variable int a and initialize it to 5.
//   Now, write a function which does not return anything, but can set the value of 
//   an integer to 10.


void f(int *a){
    *a = 10;
}

//Use this function to set the value of a to 10.
   
//Use printf to demonstrate that the value of a changed.
   
//Now, put a breakpoint at int a = 5, and trace the code.

// 2. Implement a function that performs Insertion Sort https://en.wikipedia.org/wiki/Insertion_sort#Algorithm
//   The function should take in an array of integers, and modify the array so that it's 
//   sorted in increasing order.

void insertion_sort(int arr[], int size){
    int i, key, end;
    for (i = 1; i < size; i++){
        key = arr[i];
        end = i - 1;
        
        while (end >= 0 && arr[end] > key){
            arr[end + 1] = arr[end];
            end = end - 1;
        }
        arr[end + 1] = key;
    }
}

void print_arr(int *arr, int size){
    int i = 0;
    for (i = 0; i < size; i++){
        printf("%d \n", arr[i]);
    }
}

int main(void){
    int a = 5;
    f(&a);
    printf("the value of a is now: %d\n", a);

    int arr[] = {3, 1, 5, 6, 9, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    insertion_sort(arr, n);
    print_arr(arr, n);

    return 0;
}