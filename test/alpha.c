// #define DEBUG
#include "action.h"

void alpha_SLL(void) {
    ALPHABET_t* alpha = (ALPHABET_t*)malloc(sizeof(ALPHABET_t));
    alpha = NULL;

    ACTION_t* action_1 = (ACTION_t*)malloc(sizeof(ACTION_t));
    action_1->p = action_1->m = action_1->f = action_1->b = 1;
    action_1->next = NULL;
    ACTION_t* action_2 = (ACTION_t*)malloc(sizeof(ACTION_t));
    action_2->p = action_2->m = action_2->f = action_2->b = 2;
    action_2->next = NULL;
    ACTION_t* action_3 = (ACTION_t*)malloc(sizeof(ACTION_t));
    action_3->p = action_3->m = action_3->f = action_3->b = 3;
    action_3->next = NULL;


    TEST_ASSERT_EQUAL_UINT(0, len_SLL_alpha(&alpha));
    append_alpha(&alpha, 'A', action_1);
    TEST_ASSERT_EQUAL_UINT(1, len_SLL_alpha(&alpha));
    append_alpha(&alpha, 'B', action_2);
    TEST_ASSERT_EQUAL_UINT(2, len_SLL_alpha(&alpha));
    append_alpha(&alpha, 'C', action_3);
    TEST_ASSERT_EQUAL_UINT(3, len_SLL_alpha(&alpha));

    #ifdef DEBUG 
    printf("3 letters:\n");
    print_SLL_alpha(&alpha);
    printf("\n");
    #endif

    TEST_ASSERT(alpha->character == 'A');
    del_first_alpha(&alpha);
    TEST_ASSERT_EQUAL_UINT(2, len_SLL_alpha(&alpha));
    TEST_ASSERT(alpha->character == 'B');

    del_SLL_alpha(&alpha);
    TEST_ASSERT(alpha == NULL);

    #ifdef DEBUG 
    printf("empty:\n");
    print_SLL_alpha(&alpha);
    printf("\n");
    #endif
}
