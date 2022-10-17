#ifndef SLIB_INCLUDE_SLIB_LIST_H_
#define SLIB_INCLUDE_SLIB_LIST_H_

typedef struct slib_list_node {
    struct slib_list_node* prev;
    struct slib_list_node* next;
} slib_list_node;

void __slib_list_push(slib_list_node* prev, slib_list_node* new_node,
                      slib_list_node* next);

static inline void slib_list_push_front(slib_list_node* head,
                                        slib_list_node* new_node) {
    __slib_list_push(head, new_node, head->next);
}

static inline void slib_list_push_back(slib_list_node* head,
                                       slib_list_node* new_node) {
    __slib_list_push(head->prev, new_node, head);
}

#endif  // SLIB_INCLUDE_SLIB_LIST_H_