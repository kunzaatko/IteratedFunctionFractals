#include "alpha_modification.h"
#include "axiom_string.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
typedef struct
{
    ALPHABET_t** alpha;
    node_t** axiom;
    MODIFICATION_t** mod;
} input_t;

void fprint_input(FILE* stream, input_t* input);
void print_input(input_t* input);

//allokuje parametry input do struktury input_t
int load_input(input_t* out, FILE* input);
