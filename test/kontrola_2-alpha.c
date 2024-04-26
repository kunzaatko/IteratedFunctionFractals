#include "../program/alpha_mod-module.h"
#include <stdio.h>
#include <stdlib.h>

void print_SLL_alpha(ALPHABET_t** head_ref)
{
    ALPHABET_t* print = *head_ref;
    while (print != NULL) {
        printf("%c - (%.1f, %.1f, %d, %d), \n", print->character, print->action->p, print->action->m, print->action->f, print->action->b);
        print = print->next;
    }
}

int main()
{
    ALPHABET_t* alpha = (ALPHABET_t*)malloc(sizeof(ALPHABET_t));
    alpha = NULL;
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
    append_alpha(&alpha, 'A', action_1);
    append_alpha(&alpha, 'B', action_2);
    append_alpha(&alpha, 'C', action_3);
    print_SLL_alpha(&alpha);
    printf("VYMAZANÝ:");
    del_SLL_alpha(&alpha);
    print_SLL_alpha(&alpha);

    return 0;
}
