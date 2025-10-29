#include "load.h"

void load() {
    input_t* out = (input_t*)malloc(sizeof(input_t));
    FILE* input_file = fopen("test/input.txt", "r");
    TEST_ASSERT(input_file != NULL);
    load_input(out,input_file);
    print_input(out);

    // FIX: Printing of alphabet causes Segmentation fault <27-04-24> 
}
