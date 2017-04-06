/* llist_node.c

   A doubly-linked list implementation
*/

#include <stdlib.h>

#include "dlist_node.h"
// create (i.e., malloc) a new node
dlist_node* new_node(int data, dlist_node* next, dlist_node* prev)
{
  dlist_node* n = malloc(sizeof(dlist_node));
  n->data = data;
  n->next = next;
  n->prev = prev;
  return n;

}

// insert a new node after the given one
// Precondition: Supplied node is not NULL.
void insert_after(dlist_node* n, int data)
{
  n->next = new_node(data, n->next, n);
  if (n->next->next != NULL) {
    n->next->next->prev = n->next;
  }

}

// insert a new node before the given one
// Precondition: Supplied node is not NULL.
void insert_before(dlist_node* n, int data);
{
  n->prev = new_node(data, n, n->prev);
  if (n->prev->prev != NULL) {
    n->prev->prev->next = n->prev;
  }
}


// delete the given node
// Precondition: Supplied node is not NULL.
void delete_node(dlist_node* n)
{
  if (n->prev == NULL && n->next == NULL){ //only node in the list
    free(n);
  }
  else if (n->prev == NULL){ //if node is in the front
    llist_node* delendum = n->next;
    delendum->prev = NULL;
    free(delendum->prev);
  }
  else if (n->next == NULL){ //if node is in the back
    llist_node* delendum = n->prev;
      delendum->next = NULL;
    free(delendum->next);i
  } else if {
    llist_node* delendum = n->next;
    n->next = n->prev->next;
    n->prev = n->next->prev;
    free(delendum);
  }
}



// return a pointer to the nth node in the list. If n is
// the length of the list, this returns NULL, but does not error.
// Precondition: the list has at least n nodes
dlist_node* nth_node(dlist_node* head, int n);
{
  //iterates through in order to return the pointer to the given head
  for( ; n > 0; n--, head = head->next)
    ;
  return head;
}

// return a pointer to the nth previous node in the list. (That is,
// this uses `prev` pointers, not `next` pointers.) If n is
// the length of the list, this returns NULL, but does not error.
// Precondition: the list has at least n nodes
dlist_node* nth_node_prev(dlist_node* tail, int n);
{
  for( ; n > 0; n--, tail = tail->prev)
  ;
  return tail;
}

// free an entire linked list. The list might be empty.
void free_dlist(dlist_node* head)
  {
    llist_node* current = head;
    while(current)
    {
      head = current;
      current = current->next;
      free(head);
    }
  }
// create a linked list that stores the same elements as the given array.
// Postcondition: returns the head element
dlist_node* from_array(int n, int a[n])
{
  llist_node* result = NULL;
  llist_node* prevresult != NULL;
  for(int i = n-1; i >= 0; i--)
  {
    result = new_node(a[i], result, result-> prev);
  }
  return result;

}

// fill in the given array with the elements from the list.
// Returns the number of elements filled in.
// Postcondition: if n is returned, the first n elements of the array
// have been copied from the linked list
int to_array(dlist_node* head, int n, int a[n])
{
  int i;
  for(i = 0; i < n && head; i++, head = head->next)
  {
    a[i] = head->data;
  }
  return i;
}

// gets the length of a list
int length(dlist_node* head)
{
  int len = 0;
  for( ; head; head = head->next, len++)
    ;
  return len;
}
