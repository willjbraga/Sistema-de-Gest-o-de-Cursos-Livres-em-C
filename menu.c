#include <stdio.h>
#include "menu.h"

int menu_principal(void){
    int op;
    do{
        printf("\n=== SISTEMA DE CURSOS LIVRES ===\n");
        printf("1 - Alunos\n");
        printf("2 - Cursos\n");
        printf("3 - Inscricoes\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();
    }while(op < 0 || op > 3);
    return op;
}

int menu_alunos(void){
    int op;
    do{
        printf("\n--- MENU ALUNOS ---\n");
        printf("1 - Cadastrar\n");
        printf("2 - Listar todos alunos\n");
        printf("3 - Pesquisar aluno por cpf\n");
        printf("4 - Atualizar\n");
        printf("5 - Remover\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();
    }while(op < 0 || op > 5);
    return op;
}


int menu_cursos(void){
    int op;
    do{
        printf("\n--- MENU CURSOS ---\n");
        printf("1 - Cadastrar\n");
        printf("2 - Listar todos cursos\n");
        printf("3 - Pesquisar curso por codigo\n");
        printf("4 - Atualizar\n");
        printf("5 - Remover\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();
    }while(op < 0 || op > 5);
    return op;
}

int menu_inscricoes(void){
    int op;
    do{
        printf("\n--- MENU INSCRICOES ---\n");
        printf("1 - Cadastrar\n");
        printf("2 - Listar todas inscricoes\n");
        printf("3 - Pesquisar inscricao por ID\n");
        printf("4 - Atualizar\n");
        printf("5 - Remover\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();
    }while(op < 0 || op > 5);
    return op;
}
