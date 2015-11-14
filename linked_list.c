#include "linked_list.h"
//node *head = NULL;

node *create_list(void* data)
{
  node *ptr = (node *)calloc(1, sizeof(node));

  if (NULL == ptr)
    return NULL;

  ptr->data = data;
  ptr->next = NULL;
  ptr->prev = NULL;

  //head = curr = ptr;

  return ptr;
}

node *add_to_list(node *head,void* data, bool add_to_end)
{
  if (NULL == head)
    return create_list(data);

  node *ptr = (node *)calloc(1, sizeof(node));

  if (NULL == ptr)
    return NULL;

  ptr->data = data;
  ptr->next = NULL;
  ptr->prev = NULL;
    node *curr = NULL;
  if (add_to_end) {
      curr=head;
      while (curr->next != NULL)
        {
            curr = curr->next;
        }
    curr->next = ptr;
    ptr->prev = curr;
  } else {
    ptr->next = head;
    head->prev = ptr;
    //head = ptr;
  }

  return ptr;
}

node *search_list(node *head, void* data)
{
  node *ptr = head;
 // node *tmp = NULL;
  bool found = false;

  while (ptr != NULL)
  {
    if (ptr->data == data) {
      found = true;
      break;
    }

   // tmp = ptr;
    ptr = ptr->next;
  }

  if (found == true)
    {
    return ptr;
  }

  return NULL;
}

node* delete_item(node *head, void* data)
{
     node *prev = NULL;
  node* ptr = search_list(head, data);



  if (ptr == NULL)
    return head;

    prev = ptr->prev;
  if (prev != NULL) {

    node *next = ptr->next;
    prev->next = next;
    next->prev = prev;
  }
  else
    head= ptr->next;

  free(ptr);
  ptr = NULL;
  return head;
}
node* delete_item_at(node *head, int at)
{
     node *prev = NULL;
  node* ptr = get(head, at);

  if (ptr == NULL)
    return head;

    prev = ptr->prev;
  if (prev != NULL)
  {

    node *next = ptr->next;
    if(next)
    {
     prev->next = next;
     next->prev = prev;
    }
    else
    {
       prev->next=next; 
    }    
  }
  else
    head= ptr->next;

  free(ptr);
  ptr = NULL;
  return head;
}
void print_list(node *head)
{
  node *ptr = head;

  while (ptr->next) {
    printf("%s\n", (char*)ptr->data);
    ptr = ptr->next;
  }
}
node* get(node* head, int pos )
{
    int curr=1;
    node *ptr = head;
    for(;curr<pos && ptr!=NULL;curr++)
    {
        ptr=ptr->next;
    }
    return ptr;

}
void* get_att(node* head,int pos)
{
    node* ptr=get(head, pos);
    if(ptr!=NULL)
    {
        void* res=ptr->data;
        return res;
    }
    return NULL;


}
int size(node* head)
{
    int size=0;
     node *ptr = head;
  while (ptr->next) {
    size++;
    ptr = ptr->next;
  }
  return size;
}
