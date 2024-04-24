#include "../program/axiom_string-module.h"
#include <stdio.h>
#include <stdlib.h>

void print_DLL_axiom(node_t** head_ref)
{
    node_t* print = *head_ref;
    while (print != NULL) {
        printf("(%c)", print->character);
        print = print->next;
    }
    printf("\n");
}

int main()
{
    node_t* axiom = (node_t*)malloc(sizeof(node_t));
    axiom = NULL;
    insertAfter(&axiom, axiom, 'A');
    print_DLL_axiom(&axiom);
    insertBefore(&axiom, axiom, 'B');
    print_DLL_axiom(&axiom);
    push(&axiom, 'C');
    print_DLL_axiom(&axiom);
    append(&axiom, 'D');
    print_DLL_axiom(&axiom);
    del_Node(&axiom, axiom->next);
    print_DLL_axiom(&axiom);
    del_DLL(&axiom);
    print_DLL_axiom(&axiom);
    return 0;
}
