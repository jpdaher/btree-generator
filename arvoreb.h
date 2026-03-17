#ifndef ARVOREB_H
#define ARVOREB_H

#include <stdbool.h>

#define Tam 5

typedef struct btree{
    int keys[2*Tam-1];
    struct btree *children[2*Tam];
    int n;
    bool leaf;
} btree;

btree* createnode(bool leaf);
btree* searchnode(btree* node, int key);
void insert(btree* node, int key);
void insertnonfull(btree* node, int key);
void splitchild(btree* parent, int i, btree* child);

#endif