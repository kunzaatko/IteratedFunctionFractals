#include "axiom_string.h"
#include <stdio.h>
#include <stdlib.h>

//akce odpovídající znaku
typedef struct ACTION_t //Je to SLL
{
    float p; //počet stupňů doprava
    float m; //počet stupňů doleva
    int f; //pohyb dopředu ano/ne
    int b; //pohyb dozadu ano/ne
    struct ACTION_t* next; //ukazatel na další akci
} ACTION_t;

typedef struct MODIFICATION_t {
    char character; //písmeno, které se upravuje
    node_t** string_head_ref; //to, čím bude nahrazený znak
    struct MODIFICATION_t* next; //předpis další modifikace
} MODIFICATION_t;

//abeceda znak
typedef struct ALPHABET_t //Je to SLL
{
    char character; //znak ve stringu pohybů
    ACTION_t* action; //akce odpovídající znaku
    struct ALPHABET_t* next; //ukazatel na další znak abecedy
} ALPHABET_t;

//vytisknout celou abecedu
void print_SLL_alpha(ALPHABET_t** head_ref)
{
    printf("ABECEDA:\n");
    ALPHABET_t* print = *head_ref;
    while (print != NULL) {
        printf("%c - (PROTISMĚRU: %.1f°,POSMĚRU: %.1f°, %dx dopředu, %dx dozadu), \n", print->character, print->action->p, print->action->m, print->action->f, print->action->b);
        print = print->next;
    }
    printf("\n");
}

//vytisknout celý seznam akcí
void print_SLL_action(ACTION_t** head_ref)
{
    ACTION_t* print = *head_ref;
    while (print != NULL) {
        printf("(%.1f, %.1f, %d, %d)\n", print->p, print->m, print->f, print->b);
        print = print->next;
    }
}

//přidání na konec
void append_alpha(ALPHABET_t** head_ref, char new_character /*nový písmeno abecedy*/, ACTION_t* new_action /* akce odpovídající znaku */)
{
    if ((*head_ref) == NULL) {
        (*head_ref) = (ALPHABET_t*)malloc(sizeof(ALPHABET_t));
        (*head_ref)->character = new_character;
        (*head_ref)->action = new_action;
        (*head_ref)->next = NULL;
    } else {
        // najit konec seznamu
        ALPHABET_t* last = *head_ref;
        while (last->next != NULL) {
            last = last->next;
        }

        last->next = (ALPHABET_t*)malloc(sizeof(ALPHABET_t));
        (last->next)->character = new_character;
        (last->next)->action = new_action;
        (last->next)->next = NULL;
    }
}

void del_first_alpha(ALPHABET_t** head_ref)
{
    if ((*head_ref) != NULL) {
        ALPHABET_t* first = (*head_ref);
        *head_ref = (*head_ref)->next;
        free(first);
    }
}

void del_SLL_alpha(ALPHABET_t** head_ref)
{
    while ((*head_ref) != NULL) {
        del_first_alpha(head_ref);
    }
}

void append_action(ACTION_t** head_ref, ACTION_t* action)
{
    if ((*head_ref) == NULL) {
        *head_ref = action;
        action->next = NULL;
    } else {
        //najít konec seznamu
        ACTION_t* last = *head_ref;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = action;
        action->next = NULL;
    }
}

void del_first_action(ACTION_t** head_ref)
{
    if (*head_ref != NULL) {
        ACTION_t* first = *head_ref;
        *head_ref = (*head_ref)->next;
        free(first);
    }
}

void del_SLL_action(ACTION_t** head_ref)
{
    while (*head_ref != NULL) {
        del_first_action(head_ref);
    }
}

//vytisknout celý seznam modifikací
void print_SLL_mod(MODIFICATION_t** head_ref)
{
    MODIFICATION_t* print = (*head_ref);
    while (print != NULL) {
        printf("%c -> ", print->character);
        print_DLL_axiom(print->string_head_ref);
        print = print->next;
    }
}

void append_mod(MODIFICATION_t** head_ref, char new_character, node_t** new_string_head_ref)
{
    MODIFICATION_t* new_mod = (MODIFICATION_t*)malloc(sizeof(MODIFICATION_t));
    new_mod->next = NULL;
    new_mod->character = new_character;
    new_mod->string_head_ref = new_string_head_ref;

    if ((*head_ref) == NULL) {
        *head_ref = new_mod;
    } else {
        MODIFICATION_t* last = *head_ref;
        while ((last->next) != NULL) {
            last = last->next;
        }
        last->next = new_mod;
    }
}

void del_first_mod(MODIFICATION_t** head_ref)
{
    if ((*head_ref) != NULL) {
        MODIFICATION_t* first = *head_ref;
        *head_ref = (*head_ref)->next;
        del_DLL(first->string_head_ref);
        free(first);
    }
}

void del_SLL_mod(MODIFICATION_t** head_ref)
{
    while ((*head_ref) != NULL) {
        del_first_mod(head_ref);
    }
}

void del_input(ALPHABET_t** head_ref_alpha, ACTION_t** head_ref_action, MODIFICATION_t** head_ref_mod)
{
    del_SLL_alpha(head_ref_alpha);
    del_SLL_action(head_ref_action);
    del_SLL_mod(head_ref_mod);
}
