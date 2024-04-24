#pragma once
#include "axiom_string-module.h"
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

//abeceda znak
typedef struct ALPHABET_t //Je to SLL
{
    char character; //znak ve stringu pohybů
    ACTION_t* action; //akce odpovídající znaku
    struct ALPHABET_t* next; //ukazatel na další znak abecedy
} ALPHABET_t;

//vytisknout celou abecedu
void print_SLL_alpha(ALPHABET_t** head_ref);
//vytisknout celý seznam akcí
void print_SLL_action(ACTION_t** head_ref);

//přidání na konec
void append_alpha(ALPHABET_t** head_ref /* SLL */, char new_character /*nový písmeno abecedy*/, ACTION_t* new_action /* akce odpovídající znaku */);
//dealokuje první uzel
void del_first_alpha(ALPHABET_t** head_ref);
//dealokuje SLL alpha
void del_SLL_alpha(ALPHABET_t** head_ref /* SLL */);
//přidá akci na konec z ukazatele na akci
void append_action(ACTION_t** head_ref, ACTION_t* action);
//dealokuje první uzel
void del_first_action(ACTION_t** head_ref);
//dealokuje SLL action
void del_SLL_action(ACTION_t** head_ref);

//struktura modifikace (character se nahrazuje, modification_stringem)
typedef struct MODIFICATION_t {
    char character; //písmeno, které se upravuje
    node_t** string_head_ref; //to, čím bude nahrazený znak
    struct MODIFICATION_t* next; //předpis další modifikace
} MODIFICATION_t;

//vytisknout celý seznam modifikací
void print_SLL_mod(MODIFICATION_t** head_ref);
//Přidá modifikaci
void append_mod(MODIFICATION_t** head_ref, char new_character, node_t** new_modification_string);
//dealokuje SLL mod
void del_SLL_mod(MODIFICATION_t** head_ref);
//dealokuje první uzel
void del_first_mod(MODIFICATION_t** head_ref);

//dealokuje všechny struktury inputu
void del_input(ALPHABET_t** head_ref_alpha, ACTION_t** head_ref_action, MODIFICATION_t** head_ref_mod);
