#include <stdio.h>
#include <stdlib.h>

// struktura uzlu
typedef struct node_t {
    char character;
    struct node_t* prev;
    struct node_t* next;
} node_t;

//vytisknout celý seznam
void print_DLL_axiom(node_t** head_ref)
{
    node_t* print = *head_ref;
    printf("{");
    while (print != NULL) {
        printf("%c", print->character);
        print = print->next;
    }
    printf("}\n");
}

// přidá uzel na začátek
void push(node_t** head_ref /* DLL */, char new_character /* "nový písmeno" */)
{
    // alokování nového uzlu
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->character = new_character;
    new_node->next = (*head_ref);

    // první uzel seznamu ->
    new_node->prev = NULL;

    // pokud první prvek před přidáním existuje, tak je potřeba ukázat na první
    // prvek po přidání
    if ((*head_ref) != NULL) {
        (*head_ref)->prev = new_node;
    }
    // přeadresování ukazatel "head_ref"
    (*head_ref) = new_node;
}

// přidá uzel na konec
void append(node_t** head_ref /* DLL */, char new_character /* "nový písmeno" */)
{
    // alokování nového uzlu
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->character = new_character;
    // poslední uzel seznamu ->
    new_node->next = NULL;

    // DLL prázdný->
    if ((*head_ref) == NULL) {
        new_node->prev = NULL;
        (*head_ref) = new_node;
        return;
    }

    // nalezení posledního uzlu DLL
    node_t* last = (*head_ref);
    while (last->next != NULL) {
        last = last->next;
    }

    // ukázat na nový uzel
    last->next = new_node;

    // ukázat na "prev_node"
    new_node->prev = last;
}

// přidat uzel před "next_node" - (nekontroluju existenci "next_node" -> musím
// dávat pozor, aby existoval)
void insertBefore(node_t** head_ref /* DLL */,
    node_t* next_node /* následující uzel */,
    char new_character /* "nový písmeno" */)
{
    // alokování nového uzlu
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->character = new_character;

    // DLL prázdný || "next_node" první uzel->
    if ((*head_ref) == NULL || (*head_ref) == next_node) {
        push(head_ref, new_character);
        return;
    }

    //"new_node" je před "next_node" a není první->
    new_node->next = next_node;
    new_node->prev = next_node->prev;
    (next_node->prev)->next = new_node;
    next_node->prev = new_node;
}

// přidat uzel za "prev_node" - (nekontroluju existenci "next_node" -> musím
// dávat pozor, aby existoval)
void insertAfter(node_t** head_ref /* DLL */,
    node_t* prev_node /* předcházející uzel */,
    char new_character /* "nový písmeno" */)
{
    // alokování nového uzlu
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->character = new_character;

    // DLL prázdný->
    if ((*head_ref) == NULL) {
        append(head_ref, new_character);
        return;
    }

    //"new_node" je po "prev_node"
    new_node->prev = prev_node;
    new_node->next = prev_node->next;
    //"new_node" není na konci DLL->
    if (prev_node->next != NULL) {
        (prev_node->next)->prev = new_node;
    }
    prev_node->next = new_node;
}

// vymazat uzel "del_node" - (nekontroluju existenci "del_node" -> musím dávat
// pozor, aby existoval)
void del_Node(node_t** head_ref /* DLL */, node_t* del_node /* uzel na vymazání */)
{
    if ((*head_ref) == NULL) {
        return;
    }
    if (del_node == (*head_ref)) {
        (*head_ref) = del_node->next;
    } else {
        (del_node->prev)->next = del_node->next;
        if (del_node->next != NULL) {
            (del_node->next)->prev = del_node->prev;
        }
    }
    free(del_node);
}

void del_first_Node(node_t** head_ref)
{
    if ((*head_ref) != NULL) {
        node_t* first = *head_ref;
        *head_ref = (*head_ref)->next;
        free(first);
    }
}

// vymazat DLL
void del_DLL(node_t** head_ref /* DLL */)
{
    while ((*head_ref) != NULL) {
        del_first_Node(head_ref);
    }
}
