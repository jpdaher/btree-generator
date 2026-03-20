#ifndef ARVOREB_H
#define ARVOREB_H

#include <stdbool.h>

#define TAM 5

typedef struct Registro{
    int matricula;
    long byte_offset;
}Registro;

typedef struct btree{
    Registro dados[TAM - 1];
    struct btree *children[TAM];
    int n;
    bool leaf;
} btree;

btree* create_node(bool leaf);
void insert(btree** root, Registro reg);
void free_tree(btree* node);
Registro* search_node(btree* node, int matricula);

#endif
