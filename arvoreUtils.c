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

static void print_node_to_file(btree* node, FILE* out, int nivel) {
    if (!node) return;

    // Imprime o nível, o endereço do nó atual e se é folha
    fprintf(out, "[Nivel %d] No: %p | Folha: %s\n", 
            nivel, (void*)node, node->leaf ? "Sim" : "Nao");

    // Imprime as chaves e seus respectivos offsets
    fprintf(out, "   Chaves (Matricula:Offset): ");
    for (int i = 0; i < node->n; i++) {
        fprintf(out, "[%d:%ld] ", node->dados[i].matricula, node->dados[i].byte_offset);
    }
    fprintf(out, "\n   Filhos: ");

    // Imprime os endereços dos filhos para conferência
    if (!node->leaf) {
        for (int i = 0; i <= node->n; i++) {
            fprintf(out, "%p ", (void*)node->children[i]);
        }
        fprintf(out, "\n\n");

        // Chamada recursiva para os filhos aumentando o nível
        for (int i = 0; i <= node->n; i++) {
            print_node_to_file(node->children[i], out, nivel + 1);
        }
    } else {
        fprintf(out, "Nenhum\n\n");
    }
}

// Função principal de salvamento
bool save_tree_to_txt(btree* root, const char* output_file_name) {
    FILE* out = fopen(output_file_name, "w");
    if (!out) return false;

    fprintf(out, "--- ESTRUTURA DA ARVORE B (ORDEM %d) ---\n", TAM);
    fprintf(out, "Endereco da Raiz: %p\n\n", (void*)root);

    // Iniciamos a recursão com nível 0
    print_node_to_file(root, out, 0);

    fclose(out);
    return true;
}
