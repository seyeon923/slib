#ifndef SLIB_INCLUDE_SLIB_LIST_H_
#define SLIB_INCLUDE_SLIB_LIST_H_

#include <stddef.h>

typedef struct slib_list_node {
    struct slib_list_node* prev;
    struct slib_list_node* next;
} slib_list_node;

void __slib_list_push(slib_list_node* prev, slib_list_node* new_node,
                      slib_list_node* next);

void __slib_list_unlink(slib_list_node* node);

static inline void slib_list_init_node(slib_list_node* node) {
    node->next = node;
    node->prev = node;
}

static inline void slib_list_push_front(slib_list_node* head,
                                        slib_list_node* new_node) {
    __slib_list_push(head, new_node, head->next);
}

static inline void slib_list_push_back(slib_list_node* head,
                                       slib_list_node* new_node) {
    __slib_list_push(head->prev, new_node, head);
}

static inline slib_list_node* slib_list_pop_front(slib_list_node* head) {
    slib_list_node* front;
    if ((front = head->next) == head) {
        return front;
    }
    __slib_list_unlink(front);
    return front;
}

static inline slib_list_node* slib_list_pop_back(slib_list_node* head) {
    slib_list_node* back;
    if ((back = head->prev) == head) {
        return back;
    }
    __slib_list_unlink(back);
    return back;
}

static inline size_t slib_list_get_size(slib_list_node* head) {
    size_t num = 0;
    for (slib_list_node* p = head->next; p != head; p = p->next) {
        ++num;
    }
    return num;
}

#endif  // SLIB_INCLUDE_SLIB_LIST_H_