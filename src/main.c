#include "inputread.h"
#include "alpha_modification.h"
#include "axiom_string.h"
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

    input_t* out = (input_t*)malloc(sizeof(input_t));
    int input_loaded = load_input(out, input);
    if(input_loaded == 1){
        return 1;
    };

    //proměna
    printf("ZADEJ ČÍSLO ITERACE, KTEROU CHCEŠ VYKRESLIT:");
    int number_of_iterations;
    scanf("%d", &number_of_iterations);

    // FIX: From here it doesn't work <27-04-24> 
    //uzel po kterém se bude posouvat a hledat modifikace
    node_t* index_node = *(out->axiom);
    //pokud vypíšeme první iteraci, tak se vypíše pouze axiom
    for (int i = 1; i <= (number_of_iterations - 1); i++) {
        index_node = *(out->axiom);
        //dokud se nedostaneme na konec seznamu
        while (index_node != NULL) {
            //musíme si uložit současný uzel, na který přistupujeme, protože při modifikaci ho pak vymažeme
            node_t* index_node_next = index_node->next;
            MODIFICATION_t* index_modification = *(out->mod);
            while (index_modification != NULL) {
                if (index_modification->character == index_node->character) {
                    node_t* index_modification_string = *(index_modification->string_head_ref);
                    while (index_modification_string != NULL) {
                        insertBefore(out->axiom, index_node, index_modification_string->character);
                        index_modification_string = index_modification_string->next;
                    }
                    del_Node(out->axiom, index_node);
                }
                index_modification = index_modification->next;
            }
            index_node = index_node_next;
        }
    }
    printf("Vyjádření iterace v abecedě:");
    print_DLL_axiom(out->axiom);

    if (!zelva_init())
    return 1;

    zelva_color(255,255,255);
    index_node = *(out->axiom);
    ALPHABET_t* index_alpha = *(out->alpha);
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
        index_alpha = *(out->alpha);
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
    index_node = *(out->axiom);
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
        index_alpha = *(out->alpha);
        index_node = index_node->next;
    }
    del_DLL(out->axiom);
    del_SLL_action(&((*(out->alpha))->action));
    del_SLL_mod(out->mod);
    del_SLL_alpha(out->alpha);

    zelva_quit();
    return 0;
}
