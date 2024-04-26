#include "alpha_mod-module.h"
#include "axiom_string-module.h"
#include <stdio.h>

typedef struct input_t {
    ALPHABET_t** alpha;
    node_t** axiom;
    MODIFICATION_t** mod;
} input_t;

void load_input(input_t* out, const char* input_name)
{
    FILE* input = fopen(input_name, "r");
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

    out->alpha = &alpha;
    out->axiom = &SEZNAM;
    out->mod = &mod;

    print_DLL_axiom(out->axiom);
    print_SLL_alpha(out->alpha);
    print_SLL_mod(out->mod);
}
