//#include <arvoreUtils>
//#include <arvoreb.c>

#include <stdio.h>

void inserir() {
    int mat, tel;
    char nome[50];
    printf("\n\nDigite a matrícula: ");
    scanf("%d", &mat);
    
    printf("Digite o nome: ");
    scanf(" %s", &nome);
    
    printf("Digite o telefone: ");
    scanf("%d", &tel);
    
    printf("\nMatrícula: %d | Nome: %s | Tel: %d\n", mat, nome, tel);
}

int menu(){
    int i;

    do {
        printf("\n=== MENU ÁRVORE B ===\n");
        printf("1 - Insrir dados\n");
        printf("2 - Buscar matrícula\n");
        printf("3 - Gravar dados\n");
        printf("4 - Sair\n");
        printf("Opção selecionada: ");
        
        scanf("%d", &i);

        switch (i) {
            case 1:
                inserir();
                break;
            case 2:
                printf("Buscando...\n");
                break;
            case 3:
                printf("Gravando...\n");
            case 4:
                printf("Fechando o programa...\n");
                break;
            default:
                printf("Opção inválida! Tente de novo.\n");
        }

    } while (i != 4);
}

int main()
{
    menu();

    return 0;
}
