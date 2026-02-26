#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "alunos.h"


static void tirar_enter(char *s) {
    s[strcspn(s, "\n")] = '\0';
}

void cadastrar_aluno(Aluno **aluno, int *qtd){
    Aluno novo;
    Aluno *temp;
    char op = 's';

    while (op == 's' || op == 'S') {

        printf("\nDigite o nome do Aluno\n");
        fgets(novo.nome, 60, stdin);
        tirar_enter(novo.nome);

        printf("Digite o CPF do Aluno (Apenas numero)\n");
        fgets(novo.cpf, 12, stdin);
        tirar_enter(novo.cpf);

        if (buscar_aluno_cpf(*aluno, *qtd, novo.cpf) != -1) {
            printf("CPF ja cadastrado.\n");
            continue;
        }

        printf("Digite o Telefone do Aluno (Apenas numero)\n");
        fgets(novo.telefone, 12, stdin);
        tirar_enter(novo.telefone);

        /* cresce o vetor em +1 e salva este aluno */
        temp = (Aluno*)realloc(*aluno, (*qtd + 1) * sizeof(Aluno));
        if (temp == NULL) {
            printf("Falha ao alocar/realocar memoria.\n");
            return;
        }

        *aluno = temp;
        (*aluno)[*qtd] = novo;
        (*qtd)++;

        printf("Deseja cadastrar outro aluno em sequencia? (s/n): ");
        scanf(" %c", &op);
        getchar();
    }
}

void lista_alunos(Aluno *aluno, int qtd){
    for (int i = 0; i<qtd; i++){
        printf("\n-- Aluno %d --\n", i+1);
        printf("CPF: %s\n", aluno[i].cpf);
        printf("Nome: %s\n", aluno[i].nome);
        printf("Telefone: %s\n", aluno[i].telefone);
    }
}

void buscar_aluno(Aluno *aluno, int qtd){
    char cpf[12];
    printf("Digite o cpf do aluno\n");
    fgets(cpf, 12, stdin);
    tirar_enter(cpf);

    int achou = 0;

    for (int i = 0; i<qtd; i++){
        if(strcmp(aluno[i].cpf, cpf) == 0){
            printf("\n-- Aluno %d --\n", i+1);
            printf("CPF: %s\n", aluno[i].cpf);
            printf("Nome: %s\n", aluno[i].nome);
            printf("Telefone: %s\n", aluno[i].telefone);
            achou = 1;
            break;
        }
    }

    if(achou == 0){
        printf("Aluno nao encontrado\n");
    }
}

int buscar_aluno_cpf(Aluno *aluno, int qtd, char *cpf) {
    for (int i = 0; i < qtd; i++) {
        if (strcmp(aluno[i].cpf, cpf) == 0) return i;
    }
    return -1;
}


void atualizar_aluno(Aluno *aluno, int qtd){

    char cpf[12];

    if (qtd == 0 || aluno == NULL) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    printf("Digite o CPF do aluno que deseja atualizar os dados:\n");
    fgets(cpf, sizeof(cpf), stdin);
    tirar_enter(cpf);

    int id_aluno = buscar_aluno_cpf(aluno, qtd, cpf);
    if(id_aluno == -1){
        printf("Aluno nao encontrado\n");
        return;
    }

    printf("\nAtualizando aluno: %s\n", aluno[id_aluno].nome);

    printf("Digite o novo nome:\n");
    fgets(aluno[id_aluno].nome, sizeof(aluno[id_aluno].nome), stdin);
    tirar_enter(aluno[id_aluno].nome);

    printf("Digite o novo telefone:\n");
    fgets(aluno[id_aluno].telefone, sizeof(aluno[id_aluno].telefone), stdin);
    tirar_enter(aluno[id_aluno].telefone);

    printf("Aluno atualizado com sucesso.\n");
}

void remover_aluno(Aluno **aluno, int *qtd){
    char cpf[12];

    if (*qtd == 0 || *aluno == NULL) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    printf("Digite o CPF do aluno que deseja remover:\n");
    fgets(cpf, sizeof(cpf), stdin);
    tirar_enter(cpf);

    int id_aluno = buscar_aluno_cpf(*aluno, *qtd, cpf);
    if(id_aluno == -1){
        printf("Aluno nao encontrado\n");
        return;
    }

    for (int i = id_aluno; i < (*qtd) - 1; i++) {
        (*aluno)[i] = (*aluno)[i + 1];
    }

    (*qtd)--;

    if (*qtd == 0) {
        free(*aluno);
        *aluno = NULL;
        printf("Aluno removido.\n");
        return;
    }

    Aluno *temp = realloc(*aluno, (*qtd) * sizeof(Aluno));
    if (temp != NULL) *aluno = temp;

    printf("Aluno removido.\n");
}

