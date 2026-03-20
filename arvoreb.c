#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "arvoreb.h"

static void split_child(btree* parent, int i, btree* full_child) {
    btree* child = parent->children[i];
    btree* new_node = create_node(child->leaf);
    
    
}
static void insert_non_full(btree* node, Registro reg);

btree* create_node(bool leaf){
    btree* node = (btree*) malloc(sizeof(btree));

    if(node == NULL){
        printf("Erro de alocação de memória.\n");
        exit(1);
    }

    node->leaf = leaf;
    node->n = 0;

    for(int i = 0; i < 2*Tam; i++){
        node->children[i] = NULL;
    }
    
    return node;
}

Registro* search_node(btree* node, int matricula){
    
    if (node == NULL)
        return NULL;
        
    int i = 0;
    
    
    while(i < node->n && matricula > node->dados[i].matricula){
        i++;
    }
    
    if(i < node->n && matricula == node->dados[i].matricula){
        return &(node->dados[i]);
    }
    
    if(node->leaf){
        return NULL;
    }
    
    return search_node(node->children[i], matricula);
}

void free_tree(btree* node){
   if (node == NULL) {
        return;
    }
    
    if (!node->leaf) {
       
        for (int i = 0; i <= node->n; i++) {
            free_tree(node->children[i]);
        }
    }
    
    free(node);
}

void insert(btree** root, Registro reg){
    
}
