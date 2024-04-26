#pragma once
#include <stdio.h>
#include <stdlib.h>

//string
typedef struct node_t {
    char character;
    struct node_t* prev;
    struct node_t* next;
} node_t;

//vytisknout celý seznam
void print_DLL_axiom(node_t** head_ref);
//přidání uzlu na začátek a přesunutí adresy začátku
void push(node_t** head_ref, char new_character);
//vložení uzlu na konec a založení konce
void append(node_t** head_ref, char new_character);
//přidat uzel před "next_node" - (nekontroluju existenci "next_node" -> musím dávat pozor, aby existoval)
void insertBefore(node_t** head_ref /* DLL */, node_t* next_node /* následující uzel */, char new_character /* "nový písmeno" */);
//vložení prvku před uzel "ancestor"
void insertAfter(node_t** head_ref, node_t* ancestor, char new_character);
//vymazat uzel "del_node" - (nekontroluju existenci "del_node" -> musím dávat pozor, aby existoval)
void del_Node(node_t** head_ref /* DLL */, node_t* del_node /* uzel na vymazání */);
//dealokovat první uzel
void del_first_Node(node_t** head_ref /* DLL */);
//vymazat DLL
void del_DLL(node_t** head_ref /* DLL */);
