#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreUtils.h"

btree* load_tree_from_txt(const char* file_name) {
    FILE* f = fopen(file_name, "r");
    btree* root = create_node(true);
    if (!f) return root;

    char linha[256];
    long offset;
    // Captura o offset ANTES de ler a linha para garantir o acesso direto 
    while (offset = ftell(f), fgets(linha, sizeof(linha), f)) {
        Registro reg;
        if (sscanf(linha, "%d", &reg.matricula) == 1) {
            reg.byte_offset = offset;
            insert(&root, reg);
        }
    }
    fclose(f);
    return root;
}

static void print_node_to_file(btree* node, FILE* out) {
    if (!node) return;
    fprintf(out, "Chaves: ");
    for (int i = 0; i < node->n; i++) fprintf(out, "%d ", node->dados[i].matricula);
    fprintf(out, "| Folha: %s\n", node->leaf ? "Sim" : "Nao");
    
    if (!node->leaf) {
        for (int i = 0; i <= node->n; i++) print_node_to_file(node->children[i], out);
    }
}

bool save_tree_to_txt(btree* root, const char* output_file_name) {
    FILE* out = fopen(output_file_name, "w");
    if (!out) return false;
    fprintf(out, "Raiz: %p\n", (void*)root); // Endereço da raiz conforme pedido [cite: 11]
    print_node_to_file(root, out);
    fclose(out);
    return true;
}
