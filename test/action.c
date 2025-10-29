// #define DEBUG
#include "action.h"

void action_SLL(void)
{
    ACTION_t* action = (ACTION_t*)malloc(sizeof(ACTION_t));
    action = NULL;
    ACTION_t* action_1 = (ACTION_t*)malloc(sizeof(ACTION_t));
    action_1->p = action_1->m = action_1->f = action_1->b = 1;
    action_1->next = NULL;
    ACTION_t* action_2 = (ACTION_t*)malloc(sizeof(ACTION_t));
    action_2->p = action_2->m = action_2->f = action_2->b = 2;
    action_2->next = NULL;
    ACTION_t* action_3 = (ACTION_t*)malloc(sizeof(ACTION_t));
    action_3->p = action_3->m = action_3->f = action_3->b = 3;
    action_3->next = NULL;

    TEST_ASSERT_EQUAL_UINT(0, len_SLL_action(&action));
    append_action(&action, action_1);
    TEST_ASSERT_EQUAL_UINT(1, len_SLL_action(&action));
    append_action(&action, action_2);
    TEST_ASSERT_EQUAL_UINT(2, len_SLL_action(&action));
    append_action(&action, action_3);
    TEST_ASSERT_EQUAL_UINT(3, len_SLL_action(&action));

    #ifdef DEBUG 
    printf("3 actions:\n");
    print_SLL_action(&action);
    printf("\n");
    #endif

    TEST_ASSERT(action->p == 1);
    del_first_action(&action);
    TEST_ASSERT_EQUAL_UINT(2, len_SLL_action(&action));
    TEST_ASSERT(action->p == 2);

    del_SLL_action(&action);
    TEST_ASSERT(action == NULL);

    #ifdef DEBUG 
    printf("empty:\n");
    print_SLL_action(&action);
    printf("\n");
    #endif
}
