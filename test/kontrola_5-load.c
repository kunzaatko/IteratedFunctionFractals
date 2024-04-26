#include "../program/alpha_mod-module.h"
#include "../program/axiom_string-module.h"
#include "../program/inputread-module.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{

    input_t* out = (input_t*)malloc(sizeof(input_t));
    load_input(out, "input.txt");

    print_DLL_axiom(out->axiom);
    print_SLL_alpha(out->alpha);
    print_SLL_mod(out->mod);

    return 0;
}