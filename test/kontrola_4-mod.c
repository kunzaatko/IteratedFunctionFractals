#include "../program/alpha_mod-module.h"
#include <stdio.h>
#include <stdlib.h>

//vytisknout celý seznam modifikací
void print_SLL_mod_kontrola(MODIFICATION_t** head_ref)
{
    MODIFICATION_t* print = (*head_ref);
    while (print != NULL) {
        printf("%c -> ", print->character);
        print_DLL_axiom(print->string_head_ref);
        print = print->next;
    }
    printf("\n");
}

int main()
{
    MODIFICATION_t* mod = (MODIFICATION_t*)malloc(sizeof(MODIFICATION_t));
    mod = NULL;

    FILE* input_mod = fopen("input_kontrola_4-load_mod.txt", "r");
    if (input_mod == NULL) {
        printf("Soubor 'input.txt' nelze otevřít\n");
        return 1;
    }

    /* char charac =  */ fgetc(input_mod);

    node_t* string_head_ref_stack[3];
    for (int i = 0; i <= 2; i++) {
        string_head_ref_stack[i] = NULL;
    }

    for (int i = 0; i <= 2; i++) {
        char chara = fgetc(input_mod);
        printf("index = %d\n", i);
        while (chara != '.') {
            char charact = chara;
            append(&string_head_ref_stack[i], charact);
            chara = fgetc(input_mod);
        }

        /* charac =  */
        fgetc(input_mod);
        append_mod(&mod, 'A', &string_head_ref_stack[i]);
        printf("string po iteracích:\n");
        print_DLL_axiom(&string_head_ref_stack[i]);

        printf("seznam modifikací po iteracích:\n");
        print_SLL_mod_kontrola(&mod);
    }
    for (int i = 0; i <= 2; i++) {
        printf("string po cyklu:\n");
        print_DLL_axiom(&string_head_ref_stack[i]);
    }
    printf("seznam modifikací po cyklu:\n");
    print_SLL_mod_kontrola(&mod);
    return 0;
}

//čte správně, ale nevytváří nový &string_head_ref, takže je pro všechny ta samá a to ta poslední
