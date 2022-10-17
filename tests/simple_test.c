#include <stdio.h>

#include "include/slib/list.h"
#include "include/slib/utils.h"

typedef struct employee {
    int emp_no;
    slib_list_node list_node;
} Employee;

#define NUM_EMP 10

void print_employee_list(slib_list_node* head) {
    printf("[Head]");
    for (slib_list_node* p = head->next; p != head; p = p->next) {
        Employee* p_emp = SLIB_CONTAINER_OF(p, Employee, list_node);
        printf("<->[emp:%d]", p_emp->emp_no);
    }
    printf("<->[Head]\n");
}

int main() {
    Employee emps[NUM_EMP];
    slib_list_node head;
    slib_list_init_node(&head);

    for (int i = 0; i < NUM_EMP; ++i) {
        emps[i].emp_no = i;
        slib_list_push_front(&head, &emps[i].list_node);
    }
    print_employee_list(&head);
    printf("list size: %lu\n", slib_list_get_size(&head));

    slib_list_node* p;
    p = slib_list_pop_front(&head);
    printf("emp:%d poped!\n",
           SLIB_CONTAINER_OF(p, Employee, list_node)->emp_no);
    print_employee_list(&head);
    printf("list size: %lu\n", slib_list_get_size(&head));

    p = slib_list_pop_back(&head);
    printf("emp:%d poped!\n",
           SLIB_CONTAINER_OF(p, Employee, list_node)->emp_no);
    print_employee_list(&head);
    printf("list size: %lu\n", slib_list_get_size(&head));

    return 0;
}