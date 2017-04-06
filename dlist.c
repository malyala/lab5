/* dlist.c

   Implenetation of a doubly linked list sequence
*/

#include <stdlib.h>

#include "dlist.h"
#include "dlist_node.h"

// An abstract type for sequences
typedef struct dlist_record
{
  dlist_node* head;
  dlist_node* tail;
  int size;
} dlist_record;


// return an empty dlist. Make sure to call dlist_free when you're done
// with it.
dlist dlist_new()
  {
  dlist l = malloc(sizeof(dlist_record));
  l->head = NULL;
  l->tail = NULL;
  l->size = 0;
  dlist_free(l);
  return l;
}

// returns the number of elements in the dlist. Runs in constant time.
int dlist_size(dlist l)
{
  return l->size;
}

// appends a new element to the beginning of the dlist. Runs in constant time.
void dlist_push(dlist l, int elt)
{
  l->head = new_node(elt, l->head, l->tail);
  l->size++;
}

// removes and returns the first element in the dlist. Runs in constant time.
// precondition: there is at least one element in the dlist.
int dlist_pop(dlist l)
{
  dlist_node* old_head = l->head;
  int val = old_head->data;
  l->head = old_head->next;
  l->size--;

  free(old_head);
  return val;
}

// returns the first element in the dlist, without changing the dlist.
// Runs in constant time.
// precondition: there is at least one element in the dlist.
int dlist_peek(dlist l)
{
  return l->head->data;
}

// appends a new element to the end of the dlist. Runs in constant time.
void dlist_push_end(dlist l, int elt)
{
  l->tail = new_node(elt, l->head, l->tail);
  l->size++;
}

// removes and returns the last element in the dlist. Runs in constant time.
// precondition: there is at least one element in the dlist.
int dlist_pop_end(dlist l)
{
  dlist_node* old_head = l->tail;
  int val = old_head->data;
  l->tail = old_head->prev;
  l->size--;

  free(old_head);
  return val;
}

// returns the last element in the dlist, without changing the dlist.
// Runs in constant time.
// precondition: there is at least one element in the dlist.
int dlist_peek_end(dlist l)
{
  return l->tail->data;
}

// adds a new element into the dlist, after n existing elements.
// Traverses from whichever side of the dlist is closer.
// precondition: the list has at least n elements
void dlist_insert(dlist l, int n, int elt)
{
  int len = dlist_size(l);
  if(n == 0)
  {
    dlist_push(l, elt);
  }
  else if (len/2 < n )
  {
    dlist_node* one_before = nth_node(l->head, n-1);
    insert_after(one_before, elt);
    l->size++;
  }
  else {
    dlist_node* one_before = nth_node_prev(l->tail, n-1);
    insert_after(one_before, elt);
    l->size++;
  }
}

// retrieves the nth element of the dlist.
// Traverses from whichever side of the dlist is closer.
// precondition: the list has at least (n+1) elements
int dlist_get(dlist l, int n)
{
  int len = dlist_size(l);
  if(n == 0)
  {
    dlist_peek(l);
  }
  else if (len/2 < n )
  {
    return nth_node(l->head, n)->data;
  }
  else {
    return nth_node_prev(l->tail, n)->data;
  }
}

// sets the nth element of the dlist to a new value.
// Traverses from whichever side of the dlist is closer.
// precondition: the list has at least (n+1) elements
// postcondition: returns the old value of the element that was set
int dlist_set(dlist l, int n, int new_elt)
{
  int len = dlist_size(l);
  if(n == 0)
  {
    dlist_pop(l);
    dlist_push(l, new_elt);
  }
  else if (len/2 < n )
  {
    dlist_node* node = nth_node(l->head, n);
    int old_elt = node->data;
    node->data = new_elt;
    return old_elt;
  }
  else {
    dlist_node* node = nth_node_prev(l->tail, n);
    int old_elt = node->data;
    node->data = new_elt;
    return old_elt;
  }
}

// removes the nth element of the dlist.
// Traverses from whichever side of the dlist is closer.
// precondition: the list has at least (n+1) elements
// postcondition: returns the removed element
int dlist_remove(dlist l, int n)
{
  int len = dlist_size(l);
  if(n == 0)
  {
    dlist_pop(l);
  }
  else if (len/2 < n )
  {
    dlist_node* self = nth_node(l->head, n);
    int before = self->next->data;
    delete_node(self);
    l->size--;
    return before;

  }
  else {
    dlist_node* self = nth_node_prev(l->head, n);
    int before = self->next->data;
    delete_node(self);
    l->size--;
    return before;

  }
}

// frees an dlist. Takes O(size(l)) steps.
void dlist_free(dlist l)
{
  free_dlist(l->head);
  free(l);
}
