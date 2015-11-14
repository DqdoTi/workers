#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct node {
    void *next;
    void *prev;
    void* data;
} node;



node *create_list(void* data) ;
node *add_to_list(node *head, void* data, bool add_to_end) ;
node *search_list(node *head, void* data) ;
node* delete_item(node *head ,void* data) ;
node* delete_item_at(node *head, int at);
void print_list(node *head) ;
node* get(node* head, int i );
void* get_att(node* head,int pos);
int size(node* head);


#endif // LINKED_LIST_H_INCLUDED
