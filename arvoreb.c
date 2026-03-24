#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvoreb.h"

// Função auxiliar para criar nó
btree* create_node(bool leaf) {
    btree* node = (btree*)malloc(sizeof(btree));
    if (!node) {
        perror("Erro de alocação");
        exit(1);
    }
    node->leaf = leaf;
    node->n = 0;
    for (int i = 0; i < TAM; i++) node->children[i] = NULL;
    return node;
}

// Divide um filho cheio (y) do nó pai (x)
static void split_child(btree* x, int i, btree* y) {
    int t = (TAM + 1) / 2; // Grau mínimo aproximado
    btree* z = create_node(y->leaf);
    z->n = (TAM - 1) - t;

    for (int j = 0; j < z->n; j++) 
        z->dados[j] = y->dados[j + t];

    if (!y->leaf) {
        for (int j = 0; j <= z->n; j++) 
            z->children[j] = y->children[j + t];
    }

    y->n = t - 1;
    for (int j = x->n; j >= i + 1; j--) x->children[j + 1] = x->children[j];
    x->children[i + 1] = z;

    for (int j = x->n - 1; j >= i; j--) x->dados[j + 1] = x->dados[j];
    x->dados[i] = y->dados[t - 1];
    x->n++;
}

static void insert_non_full(btree* x, Registro reg) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && reg.matricula < x->dados[i].matricula) {
            x->dados[i + 1] = x->dados[i];
            i--;
        }
        x->dados[i + 1] = reg;
        x->n++;
    } else {
        while (i >= 0 && reg.matricula < x->dados[i].matricula) i--;
        i++;
        if (x->children[i]->n == TAM - 1) {
            split_child(x, i, x->children[i]);
            if (reg.matricula > x->dados[i].matricula) i++;
        }
        insert_non_full(x->children[i], reg);
    }
}

void insert(btree** root, Registro reg) {
    btree* r = *root;
    if (r->n == TAM - 1) {
        btree* s = create_node(false);
        *root = s;
        s->children[0] = r;
        split_child(s, 0, r);
        insert_non_full(s, reg);
    } else {
        insert_non_full(r, reg);
    }
}

Registro* search_node(btree* node, int matricula) {
    if (!node) return NULL;
    int i = 0;
    while (i < node->n && matricula > node->dados[i].matricula) i++;
    if (i < node->n && matricula == node->dados[i].matricula) return &(node->dados[i]);
    return node->leaf ? NULL : search_node(node->children[i], matricula);
}

void free_tree(btree* node) {
    if (node) {
        if (!node->leaf) {
            for (int i = 0; i <= node->n; i++) free_tree(node->children[i]);
        }
        free(node); //
    }
}
