#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "arvoreb.h"

btree* createnode(bool leaf){

    btree* node = (btree*) malloc(sizeof(btree));

    if(node == NULL){
        printf("Erro de alocação\n");
        exit(1);
    }

    node->leaf = leaf;
    node->n = 0;

     for(int i = 0; i < 2*T; i++){
            node->children[i] = NULL;
        }
    
    return node;
}

btree* searchnode(btree* node, int key){
    
    if (node == NULL)
        return NULL;
        
    int i = 0;
    
    while(i < node->n && key > node->keys[i]){
        i++;
    }
    
    if(i < node->n && key == node->keys[i]){
        return node;
    }
    
    if(node->leaf){
        return NULL;
    }
    
    return searchnode(node->children[i], key);
    
}