#include <stdio.h>

#include "include/slib/list.h"

typedef struct employee {
    int emp_no;
    slib_list_node list_node;
} Employee;

#define NUM_EMP 10

int main() {
    Employee emps[NUM_EMP];
    slib_list_node head = {&head, &head};

    for (int i = 0; i < NUM_EMP; ++i) {
        emps[i].emp_no = i;
        slib_list_push_front(&head, &emps[i].list_node);
    }

    printf("[Head]");
    for (slib_list_node* p = head.next; p != &head; p = p->next) {
        Employee* p_emp = SLIB_CONTAINER_OF(p, Employee, list_node);
        printf("<->[emp:%d]", p_emp->emp_no);
    }
    printf("<->[Head]\n");

    return 0;
}