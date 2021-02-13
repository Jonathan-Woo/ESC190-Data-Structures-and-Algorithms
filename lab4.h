#if !defined(LAB4_H)
#define LAB4_H

void insert_node(int value, int pos, struct node *head);
void delete_node(int value, struct node *head);
void print_linked_list(struct node *head);

struct node{
    int data;
    struct node *next;
};
#endif