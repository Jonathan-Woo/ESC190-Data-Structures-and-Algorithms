#include "lab4.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){
    struct node *node1 = (struct node*)malloc(sizeof(struct node));
    insert_node(5, 0, node1);
    print_linked_list(node1);
    return 0;
}