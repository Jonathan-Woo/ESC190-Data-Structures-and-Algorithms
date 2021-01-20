#include <stdio.h>
void insertion_sort_while(int *arr, int size){
    /*
     * Uses insertion sort to sort array arr of size size using a while loop
     */
    int i, g, cur_elem;
    int size_sorted = 1;

    //Go through each element, skip the first element as there's nothing behind it to
    //check against
    for (i = 1; i < size; i++){
        //temporary variable to keep track of current element. It gets overwritten later.
        cur_elem = arr[i];
        //While loop that loops as long as the current element is less than the one being
        //checked against and while we are checkign within the bounds of the array
        g = size_sorted - 1;
        while(g >= 0 && arr[g] > cur_elem) {
            arr[g + 1] = arr[g];
            g -= 1;
        }
        //If either we are at the end of the list or if the current element is greater than
        //the one being checked, the current element has found it's spot
        arr[g + 1] = cur_elem;
        //After an element is sorted, the size of the sorted list increases by one
        size_sorted += 1;
    }
}

void insertion_sort_for(int *arr, int size){
    /*
     * Uses insertion sort to sort array arr of size size using a for loop.
     */
    int size_sorted = 1;
    int cur_elem, i, e;

    //Go through each element, skip the first element as there's nothing to check it against
    for(i = 1; i < size; i++){
        //Keep track of the current element
        cur_elem = arr[i];
        //Nested loop to check the array behind it. Number of iterations of the nested loop
        //is based on the size of the array behind it. The array behind it should also
        //be sorted already
        for(e = size_sorted - 1; e > 0 - 1; e--){
            //if the current element is greater than the one being checked,
            //put it in the position to the right of it and break out of the loop.
            if (cur_elem > arr[e]){
                arr[e + 1] = cur_elem;
                break;
            }
            //if the current element is less than the one being checked,
            //advance the element being checked to the right
            else{
                arr[e + 1] = arr[e];
            }
        }
        //after sorting an element, the size of the sorted array increases by 1
        size_sorted += 1;
    }
}

void print_array(int *arr, int size){
    /*
     * Prints an integer array
     */
    int i;
    printf("[");
    for (i = 0; i < size; i += 1){
        printf("%d ", arr[i]);
    }
    printf("\b]\n");
}

int main() {
    int arr[6] = {3,1,5,6,9,2};
    insertion_sort_for(arr, 6);
    insertion_sort_while(arr,6);
    print_array(arr, 6);
}
