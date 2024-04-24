#include "../program/alpha_mod-module.h"
#include <stdio.h>
#include <stdlib.h>

void print_SLL_action(ACTION_t** head_ref)
{
    ACTION_t* print = *head_ref;
    while (print != NULL) {
        printf("(%.1f, %.1f, %d, %d)\n", print->p, print->m, print->f, print->b);
        print = print->next;
    }
}
void print_action(ACTION_t* print)
{
    printf("(%.1f, %.1f, %d, %d)\n", print->p, print->m, print->f, print->b);
}

int main()
{
    ACTION_t* ACTION = (ACTION_t*)malloc(sizeof(ACTION_t));
    ACTION = NULL;
    ACTION_t* action_1 = (ACTION_t*)malloc(sizeof(ACTION_t));
    action_1->p = 1;
    action_1->m = 2;
    action_1->f = 3;
    action_1->b = 4;
    action_1->next = NULL;
    ACTION_t* action_2 = (ACTION_t*)malloc(sizeof(ACTION_t));
    action_2->p = 5;
    action_2->m = 6;
    action_2->f = 7;
    action_2->b = 8;
    action_2->next = NULL;
    ACTION_t* action_3 = (ACTION_t*)malloc(sizeof(ACTION_t));
    action_3->p = 9;
    action_3->m = 10;
    action_3->f = 11;
    action_3->b = 12;
    action_3->next = NULL;
    append_action(&ACTION, action_1);
    append_action(&ACTION, action_2);
    append_action(&ACTION, action_3);
    print_SLL_action(&ACTION);
    del_SLL_action(&ACTION);
    printf("VYMAZÁNO:");
    print_SLL_action(&ACTION);

    return 0;
}
