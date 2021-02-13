#if !defined(LAB4_H)
#define LAB4_H

void insert_node(void);
void delete_node(void);
void print_linked_list(void);

struct node{
    int data;
    struct node *next;
};
#endif