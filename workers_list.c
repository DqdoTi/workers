#include "workers_list.h"

node* add_worker(node *head, worker *wrkr)
{
    return add_to_list(head,(void *) wrkr, 0);

}
node* remove_worker(node *head, worker *wrkr)
{
    return delete_item(head,(void *)wrkr);
}
node* remove_worker_at(node *head,  int at)
{
    return delete_item_at(head,at);
}
node* get_worker(node* head, int pos )
{
    return get(head,pos);
}
worker* get_worker_at(node *head, int pos)
{
    return (worker *) get_att(head,pos);

}
int size_workers(node* head)
{
    return size( head);
}
void print_workers(node* print)
{
    node*head = print;
    worker* tmp=NULL;
    while (head!=NULL)
    {
        tmp= (worker *) head->data;
        printf("worker  id= %d, health = %d x_pos= %d, y_pos= %d\n",tmp->id,tmp->health,tmp->x_pos,tmp->y_pos);
        head = head->next;
    }
}

