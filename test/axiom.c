#include "axiom.h"

void axiom_SLL(void) {
    node_t* axiom = (node_t*)malloc(sizeof(node_t));
    axiom = NULL;
    TEST_ASSERT_EQUAL_UINT(len_DLL(&axiom), 0);

    insertAfter(&axiom, axiom, 'A');
    TEST_ASSERT_EQUAL_UINT(len_DLL(&axiom), 1);
    #ifdef DEBUG
    print_DLL_axiom(&axiom);
    #endif

    insertBefore(&axiom, axiom, 'B');
    TEST_ASSERT_EQUAL_UINT(len_DLL(&axiom), 2);
    #ifdef DEBUG
    print_DLL_axiom(&axiom);
    #endif

    push(&axiom, 'C');
    TEST_ASSERT_EQUAL_UINT(len_DLL(&axiom), 3);
    #ifdef DEBUG
    print_DLL_axiom(&axiom);
    #endif

    append(&axiom, 'D');
    TEST_ASSERT_EQUAL_UINT(len_DLL(&axiom), 4);
    #ifdef DEBUG
    print_DLL_axiom(&axiom);
    #endif

    del_Node(&axiom, axiom->next);
    TEST_ASSERT_EQUAL_UINT(len_DLL(&axiom), 3);
    #ifdef DEBUG
    print_DLL_axiom(&axiom);
    #endif

    del_DLL(&axiom);
    TEST_ASSERT_EQUAL_UINT(len_DLL(&axiom), 0);
    #ifdef DEBUG
    print_DLL_axiom(&axiom);
    #endif
}
