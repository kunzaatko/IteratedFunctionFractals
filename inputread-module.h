#include "alpha_mod-module.h"
#include "axiom_string-module.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
typedef struct
{
    ALPHABET_t** alpha;
    node_t** axiom;
    MODIFICATION_t** mod;
} input_t;

//allokuje parametry input do struktury input_t
void load_input(input_t* out, const char* input_name);
