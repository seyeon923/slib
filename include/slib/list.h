#ifndef SLIB_INCLUDE_SLIB_LIST_H_
#define SLIB_INCLUDE_SLIB_LIST_H_

#include <stddef.h>

typedef struct slib_list_node {
    struct slib_list_node* prev;
    struct slib_list_node* next;
} slib_list_node_t;

#ifdef __cplusplus
extern "C" {
#endif
void __slib_list_push(slib_list_node_t* prev, slib_list_node_t* new_node,
                      slib_list_node_t* next);

void slib_list_unlink(slib_list_node_t* node);
#ifdef __cplusplus
}
#endif

static inline int slib_list_is_empty(slib_list_node_t* head) {
    return head->next == head && head->prev == head;
}

// Init list node
// Set both node->next, node->prev to NULL
static inline void slib_list_init_node(slib_list_node_t* node) {
    node->next = node;
    node->prev = node;
}

// Push new_node to front of the list
static inline void slib_list_push_front(slib_list_node_t* head,
                                        slib_list_node_t* new_node) {
    __slib_list_push(head, new_node, head->next);
}

// Push new_node to back of the list
static inline void slib_list_push_back(slib_list_node_t* head,
                                       slib_list_node_t* new_node) {
    __slib_list_push(head->prev, new_node, head);
}

// Pop first(front) node from the list and return the poped node
// If empty list, return null
static inline slib_list_node_t* slib_list_pop_front(slib_list_node_t* head) {
    slib_list_node_t* front;
    if ((front = head->next) == head) {
        return NULL;
    }
    slib_list_unlink(front);
    return front;
}

// Pop last(back) node from the list and return the poped node
// If empty list, return null
static inline slib_list_node_t* slib_list_pop_back(slib_list_node_t* head) {
    slib_list_node_t* back;
    if ((back = head->prev) == head) {
        return NULL;
    }
    slib_list_unlink(back);
    return back;
}

// Return number of nodes in the list by iterating all nodes
static inline size_t slib_list_get_size(slib_list_node_t* head) {
    size_t num = 0;
    for (slib_list_node_t* p = head->next; p != head; p = p->next) {
        ++num;
    }
    return num;
}

// Return if node is in the list
static inline int slib_list_has_node(slib_list_node_t* head,
                                     slib_list_node_t* node) {
    for (slib_list_node_t* p = head->next; p != head; p = p->next) {
        if (p == node) {
            return 1;
        }
    }
    return 0;
}

// Return idx-th node from the list(0-based index)
// If empty list or invalid idx, return null
static inline slib_list_node_t* slib_list_get_nth(slib_list_node_t* head,
                                                  size_t idx) {
    if (head->next == head) {
        return NULL;
    }

    slib_list_node_t* p;
    size_t i;
    for (p = head->next, i = 0; p != head; p = p->next, ++i) {
        if (i == idx) {
            return p;
        }
    }
    return NULL;
}

// Pop idx-th node from the list and return it(0-based index)
// If empty list or invalid idx, no action, and return null
static inline slib_list_node_t* slib_list_pop_nth(slib_list_node_t* head,
                                                  size_t idx) {
    slib_list_node_t* nth = slib_list_get_nth(head, idx);
    slib_list_unlink(nth);
    return nth;
}

// Push node to idx-th node in the list(0-based index)
// If empty list or invalid idx, push back to the list
static inline void slib_list_push_nth(slib_list_node_t* head,
                                      slib_list_node_t* node, size_t idx) {
    slib_list_node_t* nth;
    if ((nth = slib_list_get_nth(head, idx)) == NULL) {
        slib_list_push_back(head, node);
    } else {
        __slib_list_push(nth->prev, node, nth);
    }
}

#endif  // SLIB_INCLUDE_SLIB_LIST_H_