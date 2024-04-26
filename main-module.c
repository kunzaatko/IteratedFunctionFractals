#include "inputread-module.h"
#include "alpha_mod-module.h"
#include "axiom_string-module.h"
#include "zelva.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char* input_name = argc > 1 ? argv[1] : "input.txt";

    FILE* input = fopen(input_name, "r");
    if (input == NULL) {
        printf("File '%s' cannot be opened\n", input_name);
    }

    // //LOAD_ALPHA
    // ALPHABET_t* alpha = (ALPHABET_t*)malloc(sizeof(ALPHABET_t));
    // alpha = NULL;
    // ACTION_t* action = (ACTION_t*)malloc(sizeof(ACTION_t));
    // action = NULL;
    //
    // fscanf(input, "ABECEDA {\n");
    //
    // char character;
    // char end_alpha = fgetc(input);
    //
    // while (end_alpha != '}') {
    //     ACTION_t* action_next = (ACTION_t*)malloc(sizeof(ACTION_t));
    //     character = end_alpha;
    //     fscanf(input, " - (%f,%f,%d,%d);\n", &(action_next->p), &(action_next->m),
    //         &(action_next->f), &(action_next->b));
    //     end_alpha = fgetc(input);
    //     append_action(&action, action_next);
    //     append_alpha(&alpha, character,
    //         action_next);
    // }
    // fscanf(input, ";\n"); //už jsem pozicí v input těsně před "AXIOM"
    // print_SLL_alpha(&alpha);
    //
    // //LOAD_AXIOM
    // node_t* SEZNAM = (node_t*)malloc(sizeof(node_t));
    // SEZNAM = NULL;
    //
    // fscanf(input, "AXIOM {");
    //
    // char new_axiom_char = fgetc(input);
    //
    // while (new_axiom_char != '}') {
    //     char char_s = new_axiom_char;
    //     append(&SEZNAM, char_s);
    //     new_axiom_char = fgetc(input);
    // }
    // fscanf(input, ";\n"); //už jsem pozicí těsně před "GENERACNI PROMENA"
    // printf("AXIOM - ");
    // print_DLL_axiom(&SEZNAM);
    //
    // //LOAD_MOD
    // MODIFICATION_t* mod = (MODIFICATION_t*)malloc(sizeof(MODIFICATION_t));
    // mod = NULL;
    //
    // printf("\nMODIFIKACE:\n");
    // //z nějakýho důvodu nefungoval "fscanf"
    // while (fgetc(input) != '{') {
    //     fgetc(input);
    // }
    // fgetc(input);
    //
    // fpos_t pos;
    // fgetpos(input, &pos);
    // char countingchar = fgetc(input);
    // int number_of_modifications = 0;
    // while (countingchar != '}') {
    //     if (countingchar == ';') {
    //         number_of_modifications++;
    //     }
    //     countingchar = fgetc(input);
    // }
    // node_t* string_head_ref_stack[number_of_modifications];
    // for (int i = 0; i <= (number_of_modifications - 1); i++) {
    //     string_head_ref_stack[i] = NULL;
    // }
    // fsetpos(input, &pos);
    //
    // char new_mod = fgetc(input);
    // for (int i = 0; i <= (number_of_modifications - 1); i++) {
    //     char character = new_mod;
    //     fscanf(input, " -> ");
    //
    //     char new_char = fgetc(input);
    //     while (new_char != ';') {
    //         char character = new_char;
    //         append(&string_head_ref_stack[i], character);
    //         new_char = fgetc(input);
    //     }
    //     fscanf(input, "\n");
    //     new_mod = fgetc(input);
    //     append_mod(&mod, character, &string_head_ref_stack[i]);
    // }
    // print_SLL_mod(&mod);
    // fscanf(input, ";");
    //
    // char end = fgetc(input);
    // if (end == EOF) {
    //     printf("\ninput loaded successfully\n\n");
    // } else {
    //     printf("\nthere is some problem with the input format\n\n");
    //     return 1;
    // }

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
    fscanf(input, ";\n");

    char end = fgetc(input);
    if (end == EOF) {
        printf("\ninput loaded successfully\n\n");
    } else {
        printf("\nthere is some problem with the input format\n\n");
        return 1;
    }

    input_t out;
    out.alpha = &alpha;
    out.axiom = &SEZNAM;
    out.mod = &mod;

    //proměna
    printf("ZADEJ ČÍSLO ITERACE, KTEROU CHCEŠ VYKRESLIT:");
    int number_of_iterations;
    scanf("%d", &number_of_iterations);
    //uzel po kterém se bude posouvat a hledat modifikace
    node_t* index_node = *(out.axiom);
    //pokud vypíšeme první iteraci, tak se vypíše pouze axiom
    for (int i = 1; i <= (number_of_iterations - 1); i++) {
        index_node = *(out.axiom);
        //dokud se nedostaneme na konec seznamu
        while (index_node != NULL) {
            //musíme si uložit současný uzel, na který přistupujeme, protože při modifikaci ho pak vymažeme
            node_t* index_node_next = index_node->next;
            MODIFICATION_t* index_modification = *(out.mod);
            while (index_modification != NULL) {
                if (index_modification->character == index_node->character) {
                    node_t* index_modification_string = *(index_modification->string_head_ref);
                    while (index_modification_string != NULL) {
                        insertBefore(out.axiom, index_node, index_modification_string->character);
                        index_modification_string = index_modification_string->next;
                    }
                    del_Node(out.axiom, index_node);
                }
                index_modification = index_modification->next;
            }
            index_node = index_node_next;
        }
    }
    printf("Vyjádření iterace v abecedě:");
    print_DLL_axiom(out.axiom);


    if (!zelva_init())
    return 1;

    zelva_color(255,255,255);
    index_node = *(out.axiom);
    ALPHABET_t* index_alpha = *(out.alpha);
    double move_size = 1;

typedef struct maxs_t{
    double X_max;
    double Y_max;
    double X_min;
    double Y_min;
} maxs_t;

maxs_t max;
max.X_max = max.Y_max = max.X_min = max.Y_min = 0;

    while (index_node != NULL){
        while (index_alpha != NULL) {
            if (index_node->character == index_alpha->character) {
                doleva (index_alpha->action->p);
                doprava(index_alpha->action->m);
                dopredu((index_alpha->action->f)*move_size);
                dozadu((index_alpha->action->b)*move_size);
                break;
            }
            else {
                index_alpha = index_alpha->next;
            }
        }
        index_alpha = *(out.alpha);
        index_node = index_node->next;
        pos_t XYpos = XY_pos();
        if (XYpos.X > max.X_max) {
            max.X_max = XYpos.X;
        }
        else if (XYpos.Y > max.Y_max) {
            max.Y_max = XYpos.Y;
        }
        else if (XYpos.X < max.X_min) {
            max.X_min = XYpos.X;
        }
        else if (XYpos.Y < max.Y_min) {
            max.Y_min = XYpos.Y;
        }
    }

    move_size = 600/(max.Y_max - max.Y_min);
    if (move_size > 800/(max.X_max - max.X_min )) {
        move_size = 800/(max.X_max - max.X_min );
    }

    zelva_reset();

//aby se fraktál vykreslila hezky doprostřed, tak posuneme začátek ale neviditelně
zelva_color(255,255,255);
max.X_max = max.X_max*move_size; max.Y_max = max.Y_max*move_size; max.X_min = max.X_min*move_size; max.Y_min = max.Y_min*move_size;
double width = max.X_max - max.X_min;
double height = max.Y_max - max.Y_min;
//X-souřadnice
dopredu(((width/2) - max.X_max));
//Y-souřadnice
doleva(90);
dopredu((height/2) - max.Y_max);
doprava(90);

zelva_color(0,0,0);

    // Zde se bude kreslit...
    index_node = *(out.axiom);
    while (index_node != NULL) {
        while (index_alpha != NULL) {
            if (index_alpha->character == index_node->character)
            {
                doleva (index_alpha->action->p);
                doprava(index_alpha->action->m);
                dopredu((index_alpha->action->f)*move_size);
                dozadu((index_alpha->action->b)*move_size);
                break;
            }
            else {
                index_alpha = index_alpha->next;
            }
        }
        index_alpha = *(out.alpha);
        index_node = index_node->next;
    }
    del_DLL(out.axiom);
    del_SLL_action(&((*(out.alpha))->action));
    del_SLL_mod(out.mod);
    del_SLL_alpha(out.alpha);

    zelva_quit();
    return 0;
}
