#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

void print_list_iter(struct node* head){
    /*
     * 1. For a linked list struct defined as below, write a function that prints out all
     * the data in the linked list. Do not use recursion.
     */
    struct node* cur = head;
    while (cur != NULL){
        printf("%d\n", cur->data);
        cur = cur->next;
    }
}

void print_list_cur(struct node* head){
    /*
     * Same as (1), but now use recursion.
     */
    struct node* cur = head;
    if (cur == NULL){
        return;
    }
    else{
        printf("%d\n", cur->data);
        print_list_cur(cur->next);
    }
}

struct node2{
    void *p_data; //a pointer to data (allocated with malloc)
    int type; // 0 if int, 1 if float, 2 if double
    struct node *next;
};

void append_int(struct node2* head, int a){
    /*
     * This function appends a node with integer value
     * to the linked list starting at head
     */
    struct node2* cur = head;
    //We first have to get to the end of the list
    while (cur->next != NULL){
        cur = cur->next;
    }

    //Now, we are at the last element of the list
    //We create pointers for the data and for the new node
    int *data = (int *)malloc(sizeof(int));
    struct node2 *new_node = (struct node2 *)malloc(sizeof(struct node2));

    //We attach the new node to the last node
    cur->next = new_node;

    //We set the int data and link it to the new node
    //Also, set node type
    *data = a;
    new_node->p_data = data;
    new_node->type = 0;

    //Since the new node is the last node, we set the next value to NULL
    new_node->next = NULL;
}

void append_float(struct node2* head, float a){
    /*
     * This function appends a node with float value
     * to the linked list starting at head
     */
    struct node2* cur = head;
    while (cur->next != NULL){
        cur = cur->next;
    }

    float *data = (float *)malloc(sizeof(float));
    struct node2 *new_node = (struct node2 *)malloc(sizeof(struct node2));

    cur->next = new_node;

    *data = a;
    new_node->p_data = data;
    new_node->type = 1;

    new_node->next = NULL;
}

void append_double(struct node2* head, double a){
    /*
     * This function appends a node with double value
     * to the linked list starting at head
     */
    struct node2* cur = head;
    while (cur->next != NULL){
        cur = cur->next;
    }

    double *data = (double *)malloc(sizeof(double));
    struct node2 *new_node = (struct node2 *)malloc(sizeof(struct node2));

    cur->next = new_node;

    *data = a;
    new_node->p_data = data;
    new_node->type = 2;

    new_node->next = NULL;
}

void print_node2_iter(struct node2* head){
    /*
     * Prints all elements of linked list starting at address head ITERATIVELY
     * May contain int, float, or double.
     */
    struct node2* cur = head;

    while (cur != NULL){
        if(cur->type == 0){
            int *add = cur->p_data;
            printf("%d\n", *add);
        }
        else if(cur->type == 1){
            float *add = cur->p_data;
            printf("%f\n", *add);
        }
        else if(cur->type == 2){
            double *add = cur->p_data;
            printf("%f\n", *add);
        }
        cur = cur->next;
    }
}

void print_node2_rec(struct node2* head){
    /*
     * Prints all elements of linked list starting at address head RECURSIVELY
     * May contain int, float, or double.
     */
    struct node2* cur = head;
    if (cur == NULL){
        return;
    }
    else{
        if (cur->type == 0){
            int *add = cur->p_data;
            printf("%d\n", *add);
        }
        else if (cur->type == 1){
            float *add = cur->p_data;
            printf("%f\n", *add);
        }
        else if(cur->type == 2){
            double *add = cur->p_data;
            printf("%lf\n", *add);
        }
        print_node2_rec(cur->next);
    }
}

int main() {
    //node testing
    struct node* node1 = (struct node*)malloc(sizeof(struct node));
    struct node* node2 = (struct node*)malloc(sizeof(struct node));
    struct node* node3 = (struct node*)malloc(sizeof(struct node));

    node1->data = 1;
    node2->data = 2;
    node3->data = 3;

    node1->next = node2;
    node2->next = node3;
    node3->next = NULL;

    printf("Printing node iteratively\n");
    print_list_iter(node1);
    printf("Printing node recursively\n");
    print_list_cur(node1);

    //node2 testing
    struct node2* node_1 = (struct node2*)malloc(sizeof(struct node2));
    int *test_data = (int *)malloc(sizeof(int));
    *test_data = 1;

    node_1->type = 0;
    node_1->p_data = test_data;
    node_1->next = NULL;

    append_int(node_1, 2);
    append_float(node_1, 3);
    append_double(node_1, 4);

    printf("Printing node2 iteratively\n");
    print_node2_iter(node_1);
    printf("Printing node2 recursively\n");
    print_node2_rec(node_1);

    return 0;
}
