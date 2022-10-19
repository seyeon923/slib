#include "include/slib/list.h"

void __slib_list_push(slib_list_node_t* prev, slib_list_node_t* new_node,
                      slib_list_node_t* next) {
    new_node->prev = prev;
    new_node->next = next;
    prev->next = new_node;
    next->prev = new_node;
}

void slib_list_unlink(slib_list_node_t* node) {
    if (!node) {
        return;
    }

    if (!node->prev || !node->next || node->prev == node ||
        node->next == node) {
        return;
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;

    node->next = NULL;
    node->prev = NULL;
}