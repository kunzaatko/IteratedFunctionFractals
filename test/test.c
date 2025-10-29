#include "test.h"

void setUp(void) {}
void tearDown(void) {}

int main(void) {
    UnityBegin("test/action.c");
    RUN_TEST(action_SLL);
    UnityEnd();

    UnityBegin("test/alpha.c");
    RUN_TEST(alpha_SLL);
    UnityEnd();
    
    UnityBegin("test/axiom.c");
    RUN_TEST(axiom_SLL);
    UnityEnd();

    UnityBegin("test/load.c");
    RUN_TEST(load);
    UnityEnd();

    return 0;
}
