#ifndef ARVOREB_H
#define ARVOREB_H

#include <stdbool.h>

#define TAM 5 // Ordem da árvore (m)

typedef struct Registro{
    int matricula;
    long byte_offset;// Localização exata no arquivo de texto
}Registro;

typedef struct btree{
    Registro dados[TAM - 1];
    struct btree *children[TAM];
    int n; // Quantidade atual de chaves
    bool leaf;
} btree;

btree* create_node(bool leaf);
void insert(btree** root, Registro reg);
void free_tree(btree* node);
Registro* search_node(btree* node, int matricula);

#endif
