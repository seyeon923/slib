#include "include/slib/list.h"

void __slib_list_push(slib_list_node* prev, slib_list_node* new_node,
                      slib_list_node* next) {
    new_node->prev = prev;
    new_node->next = next;
    prev->next = new_node;
    next->prev = new_node;
}
