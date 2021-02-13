#include "lab4.h"
#include <stdlib.h>
#include <stdio.h>
// 1. Write a header file for operating on linked lists (include at least inserting a value, deleting a node with a specified value 
// (if there is more than one, delete the first one), and freeing the entire linked list). 
// Write a file linkedlist.c that implements the functions declared in the h file. 
// Now write a main file with a main function that uses the functions declared in the h file. 
// Make sure that everything compiles and runs correctly.

void insert_node(int value, int pos, struct node *head){
    /* 
        Makes a new node and puts it after pos, assign value
    */
    struct node *cur = head;
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = value;
    
    struct node *p_temp = (cur[pos])->next;
    (cur[pos])->next = new_node;
    new_node->next = p_temp;
}

void delete_node(int value, struct node *head){
    /*
        break the pointer of this node to its next
    */
    struct node *cur = head;
    struct node *pre = NULL;
    
    while(cur != NULL){
        
        if (cur->data == value){
            pre->next = cur->next;
            free(cur);
            break;
        }
        pre = cur;
        cur = cur->next;
    }
   
}

void print_linked_list(struct node *head){
    while(head){
        printf("%d\n", head->data);
        head = head->next;
    }
}

// 2. In Python, write a function find(L, e) that takes in a sorted list L and an element e, and returns the lowest index in L such that L[i] == e. (-1 if there is no such index)
//    Write a function that takes in a sorted linst L and an element e, and returns the index of the highest index in L such that L[i] == e. (-1 if there is no such index).
//    The function should run in O(log(n)) time.
//    This should help you with Project 1.

