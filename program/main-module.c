#include "alpha_mod-module.h"
#include "axiom_string-module.h"
#include "zelva.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* input = fopen("input.txt", "r");
    if (input == NULL) {
        printf("Soubor 'input.txt' nelze otevřít\n");
    }

    //LOAD_ALPHA
    ALPHABET_t* alpha = (ALPHABET_t*)malloc(sizeof(ALPHABET_t));
    alpha = NULL;
    ACTION_t* action = (ACTION_t*)malloc(sizeof(ACTION_t));
    action = NULL;

    fscanf(input, "ABECEDA {\n");

    char character;
    char end_alpha = fgetc(input);

    while (end_alpha != '}') {
        ACTION_t* action_next = (ACTION_t*)malloc(sizeof(ACTION_t));
        character = end_alpha;
        fscanf(input, " - (%f,%f,%d,%d);\n", &(action_next->p), &(action_next->m),
            &(action_next->f), &(action_next->b));
        end_alpha = fgetc(input);
        append_action(&action, action_next);
        append_alpha(&alpha, character,
            action_next);
    }
    fscanf(input, ";\n"); //už jsem pozicí v input těsně před "AXIOM"
    print_SLL_alpha(&alpha);

    //LOAD_AXIOM
    node_t* SEZNAM = (node_t*)malloc(sizeof(node_t));
    SEZNAM = NULL;

    fscanf(input, "AXIOM {");

    char new_axiom_char = fgetc(input);

    while (new_axiom_char != '}') {
        char char_s = new_axiom_char;
        append(&SEZNAM, char_s);
        new_axiom_char = fgetc(input);
    }
    fscanf(input, ";\n"); //už jsem pozicí těsně před "GENERACNI PROMENA"
    printf("AXIOM - ");
    print_DLL_axiom(&SEZNAM);

    //LOAD_MOD
    MODIFICATION_t* mod = (MODIFICATION_t*)malloc(sizeof(MODIFICATION_t));
    mod = NULL;

    printf("\nMODIFIKACE:\n");
    //z nějakýho důvodu nefungoval "fscanf"
    while (fgetc(input) != '{') {
        fgetc(input);
    }
    fgetc(input);

    fpos_t pos;
    fgetpos(input, &pos);
    char countingchar = fgetc(input);
    int number_of_modifications = 0;
    while (countingchar != '}') {
        if (countingchar == ';') {
            number_of_modifications++;
        }
        countingchar = fgetc(input);
    }
    node_t* string_head_ref_stack[number_of_modifications];
    for (int i = 0; i <= (number_of_modifications - 1); i++) {
        string_head_ref_stack[i] = NULL;
    }
    fsetpos(input, &pos);

    char new_mod = fgetc(input);
    for (int i = 0; i <= (number_of_modifications - 1); i++) {
        char character = new_mod;
        fscanf(input, " -> ");

        char new_char = fgetc(input);
        while (new_char != ';') {
            char character = new_char;
            append(&string_head_ref_stack[i], character);
            new_char = fgetc(input);
        }
        fscanf(input, "\n");
        new_mod = fgetc(input);
        append_mod(&mod, character, &string_head_ref_stack[i]);
    }
    print_SLL_mod(&mod);
    fscanf(input, ";");

    char end = fgetc(input);
    if (end == EOF) {
        printf("\ninput loaded successfully\n\n");
    } else {
        printf("\nthere is some problem with the input format\n\n");
    }

    input_t out;
    out.alpha = &alpha;
    out.axiom = &SEZNAM;
    out.mod = &mod;

    //proměna
    printf("ZADEJ ČÍSLO ITERACE, KTEROU CHCEŠ VYKRESLIT:");
    int number_of_iterations;
    scanf("%d", &number_of_iterations);
    node_t* index_node = *(out.axiom);
    for (int i = 1; i <= (number_of_iterations - 1); i++) {
        index_node = *(out.axiom);
        while (index_node != NULL) {
            node_t* index_node_next = index_node->next;
            MODIFICATION_t* index_modification = *(out.mod);
            while (index_modification->next != NULL) {
                if (index_modification->character == index_node->character) {
                    node_t* index_modification_string = *(index_modification->string_head_ref);
                    while (index_modification_string->next != NULL) {
                        insertBefore(out.axiom, index_node, index_modification_string->character);
                        index_modification_string = index_modification_string->next;
                    }
                    del_Node(out.axiom, index_node);
                    break;
                }
                index_modification = index_modification->next;
            }
            index_node = index_node_next;
        }
    }
    printf("Vyjádření iterace v abecedě:");
    print_DLL_axiom(out.axiom);
}
