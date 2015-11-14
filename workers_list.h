#ifndef WORKERS_LIST_H
#define WORKERS_LIST_H
#include "worker.h"
#include "linked_list.h"

//node* node=NULL;

node* add_worker(node *head, worker *wrkr);
node* remove_worker(node *head, worker *wrkr);
node* remove_worker_at(node *head,  int at);
node* get_worker(node* head, int pos );
worker* get_worker_at(node *head, int pos);
int size_workers(node* head);
void print_workers(node* print);




#endif // WORKERS_LIST_H
