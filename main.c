#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreb.h"
#include "arvoreUtils.h"

#define ARQUIVO_REGISTROS "teste.txt"
#define ARQUIVO_SAIDA_ARVORE "saida_arvore.txt"

void menu() {
    printf("\n--- MENU ARVORE B ---");
    printf("\n1. Cadastrar");
    printf("\n2. Pesquisar");
    printf("\n3. Gravar");
    printf("\n4. Sair");
    printf("\nOpcao: ");
}

int main() {
    btree* root = load_tree_from_txt(ARQUIVO_REGISTROS);
    int opcao = 0;

    if (root == NULL) {
        printf("Erro ao inicializar a árvore.\n");
        return 1;
    }

    while (opcao != 4) {
        menu();
        if (scanf("%d", &opcao) != 1) {
            while(getchar() != '\n'); 
            continue;
        }

        if (opcao == 1) { 
            int mat;
            char nome[50], tel[20];
            printf("Matricula: "); scanf("%d", &mat);
            printf("Nome: "); scanf(" %[^\n]", nome);
            printf("Telefone: "); scanf(" %[^\n]", tel);

            // Abre o arquivo em modo leitura/escrita para checar o fim do arquivo
            FILE* f = fopen(ARQUIVO_REGISTROS, "r+");
            if (f == NULL) {
                // Se não existir, cria um novo
                f = fopen(ARQUIVO_REGISTROS, "w+");
            }
            
            if (f != NULL) {
                fseek(f, 0, SEEK_END);
                long fileSize = ftell(f);
                
                // Se o arquivo não estiver vazio, verifica se termina com \n
                if (fileSize > 0) {
                    fseek(f, -1, SEEK_END);
                    int lastChar = fgetc(f);
                    if (lastChar != '\n') {
                        fprintf(f, "\n"); // Força a quebra de linha se faltar
                    }
                }

                // Posiciona no fim para garantir que pega o offset correto da nova linha
                fseek(f, 0, SEEK_END);
                long offset = ftell(f); 
                
                // Grava o novo registro garantindo o \n no final
                fprintf(f, "%d;%s;%s\n", mat, nome, tel);
                fclose(f);

                Registro reg = {mat, offset};
                insert(&root, reg); 
                printf("Registro cadastrado com sucesso!\n");
            } else {
                printf("Erro ao abrir arquivo para escrita.\n");
            }
        } 
        else if (opcao == 2) { 
            int mat;
            printf("Matricula para pesquisa: "); scanf("%d", &mat);
            Registro* r = search_node(root, mat);
            
            if (r) {
                FILE* f = fopen(ARQUIVO_REGISTROS, "r");
                if (f != NULL) {
                    fseek(f, r->byte_offset, SEEK_SET); 
                    char buffer[256];
                    // Lê a linha e garante que imprime apenas até o \n
                    if (fgets(buffer, sizeof(buffer), f)) {
                        // Remove o \n do final do buffer se existir para evitar linhas em branco extras
                        buffer[strcspn(buffer, "\n")] = 0;
                        printf("Dados encontrados: %s\n", buffer);
                    }
                    fclose(f);
                }
            } else {
                printf("Matricula %d nao encontrada.\n", mat);
            }
        } 
        else if (opcao == 3) { 
            if (save_tree_to_txt(root, ARQUIVO_SAIDA_ARVORE)) {
                printf("Estrutura da arvore gravada em '%s'!\n", ARQUIVO_SAIDA_ARVORE);
            } else {
                printf("Erro ao gravar a arvore.\n");
            }
        }
    }

    free_tree(root); 
    printf("Sistema encerrado e memoria liberada.\n");
    
    return 0;
}
