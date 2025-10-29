#include <stdio.h>
#include <stdlib.h>

//node structure
typedef struct node_t {
    char character;
    struct node_t* prev;
    struct node_t* next;
} node_t;

// Print the axiom
void fprint_DLL_axiom(FILE* stream, node_t** head_ref)
{
    node_t* print = *head_ref;
    fprintf(stream,"{");
    while (print != NULL) {
        fprintf(stream,"%c", print->character);
        print = print->next;
    }
    fprintf(stream,"}\n");
}

void print_DLL_axiom(node_t** head_ref) {
    fprint_DLL_axiom(stdout, head_ref);
}

// Adds a node to the beginning
void push(node_t** head_ref /* DLL reference */, char new_character /* new letter */)
{
    // allocating a new node
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->character = new_character;
    new_node->next = (*head_ref);

    // first node of the list ->
    new_node->prev = NULL;

    // If the first element exists before the addition, it needs to point to the first
    // element after the addition
    if ((*head_ref) != NULL) {
        (*head_ref)->prev = new_node;
    }
    // Redirecting the pointer "head_ref"
    (*head_ref) = new_node;
}

// Adds a node to the end
void append(node_t** head_ref /* DLL */, char new_character /* new letter */)
{
    // allocating a new node
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->character = new_character;
    // last node of the list ->
    new_node->next = NULL;

    // Empty DLL
    if ((*head_ref) == NULL) {
        new_node->prev = NULL;
        (*head_ref) = new_node;
        return;
    }

    // Finding the last node of the DLL
    node_t* last = (*head_ref);
    while (last->next != NULL) {
        last = last->next;
    }

    // Point to the new node
    last->next = new_node;

    // point to "prev_node"
    new_node->prev = last;
}

// Add a node before "next_node" - (I do not check the existence of "next_node" -> I have to be careful to ensure it exists)
void insertBefore(node_t** head_ref /* DLL */,
    node_t* next_node /* next node */,
    char new_character /* new letter */)
{
    // allocating a new node
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->character = new_character;

    // DLL empty || `next_node` first node->
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

unsigned int len_DLL(node_t** head_ref) {
    unsigned int len = 0;
    node_t* current = *head_ref;
    while (current != NULL) {
        len++;
        current = current->next;
    }
    return len;
}

