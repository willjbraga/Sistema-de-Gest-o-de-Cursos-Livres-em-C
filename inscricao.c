#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inscricao.h"

static void tirar_enter(char *s) {
    s[strcspn(s, "\n")] = '\0';
}

static int gerar_id(Inscricao *insc, int qtd){
    int maior = 0;
    for(int i = 0; i < qtd; i++){
        if(insc[i].id > maior) maior = insc[i].id;
    }
    return maior + 1;
}

int buscar_inscricao_id(Inscricao *insc, int qtd, int id) {
    for (int i = 0; i < qtd; i++) {
        if (insc[i].id == id) return i;
    }
    return -1;
}

void cadastrar_inscricao(Inscricao **insc, int *qtd, Aluno *aluno, int qtd_aluno, Curso *curso, int qtd_curso){
    Inscricao novo;
    Inscricao *temp;
    char op = 's';

    while (op == 's' || op == 'S') {

        novo.id = gerar_id(*insc, *qtd);
        printf("\nID gerado da inscricao: %d\n", novo.id);

        printf("Digite o CPF do aluno (Apenas numero)\n");
        fgets(novo.cpfAluno, 15, stdin);
        tirar_enter(novo.cpfAluno);

        if (buscar_aluno_cpf(aluno, qtd_aluno, novo.cpfAluno) == -1) {
            printf("Aluno nao encontrado. Cadastre o aluno antes.\n");
            printf("Deseja tentar cadastrar outra inscricao? (s/n): ");
            scanf(" %c", &op);
            getchar();
            continue;
        }

        printf("Digite o codigo do curso\n");
        scanf("%d", &novo.codCurso);
        getchar();

        if (buscar_curso_codigo(curso, qtd_curso, novo.codCurso) == -1) {
            printf("Curso nao encontrado. Cadastre o curso antes.\n");
            printf("Deseja tentar cadastrar outra inscricao? (s/n): ");
            scanf(" %c", &op);
            getchar();
            continue;
        }

        printf("Digite a data da inscricao (DD/MM/AAAA)\n");
        fgets(novo.data, 11, stdin);
        tirar_enter(novo.data);

        printf("Pago? (0 = nao, 1 = sim)\n");
        scanf("%d", &novo.pago);
        getchar();

        temp = (Inscricao*)realloc(*insc, (*qtd + 1) * sizeof(Inscricao));
        if (temp == NULL) {
            printf("Falha ao alocar/realocar memoria.\n");
            return;
        }

        *insc = temp;
        (*insc)[*qtd] = novo;
        (*qtd)++;

        printf("\nInscricao cadastrada com sucesso.\n");

        printf("Deseja cadastrar outra inscricao em sequencia? (s/n): ");
        scanf(" %c", &op);
        getchar();
    }
}

void listar_inscricoes(Inscricao *insc, int qtd){
    if (qtd == 0 || insc == NULL) {
        printf("Nenhuma inscricao cadastrada.\n");
        return;
    }

    for (int i = 0; i < qtd; i++){
        printf("\n-- Inscricao %d --\n", i+1);
        printf("ID: %d\n", insc[i].id);
        printf("CPF do aluno: %s\n", insc[i].cpfAluno);
        printf("Codigo do curso: %d\n", insc[i].codCurso);
        printf("Data: %s\n", insc[i].data);
        printf("Pago: %d\n", insc[i].pago);
    }
}

void buscar_inscricao(Inscricao *insc, int qtd){
    int id;

    if (qtd == 0 || insc == NULL) {
        printf("Nenhuma inscricao cadastrada.\n");
        return;
    }

    printf("Digite o ID da inscricao\n");
    scanf("%d", &id);
    getchar();

    int pos = buscar_inscricao_id(insc, qtd, id);
    if (pos == -1) {
        printf("Inscricao nao encontrada\n");
        return;
    }

    printf("\n-- Inscricao encontrada --\n");
    printf("ID: %d\n", insc[pos].id);
    printf("CPF do aluno: %s\n", insc[pos].cpfAluno);
    printf("Codigo do curso: %d\n", insc[pos].codCurso);
    printf("Data: %s\n", insc[pos].data);
    printf("Pago: %d\n", insc[pos].pago);
}

void atualizar_inscricao(Inscricao *insc, int qtd){
    int id;

    if (qtd == 0 || insc == NULL) {
        printf("Nenhuma inscricao cadastrada.\n");
        return;
    }

    printf("Digite o ID da inscricao que deseja atualizar\n");
    scanf("%d", &id);
    getchar();

    int pos = buscar_inscricao_id(insc, qtd, id);
    if (pos == -1) {
        printf("Inscricao nao encontrada\n");
        return;
    }

    printf("\nAtualizando inscricao ID %d\n", insc[pos].id);

    printf("Digite a nova data (DD/MM/AAAA)\n");
    fgets(insc[pos].data, 11, stdin);
    tirar_enter(insc[pos].data);

    printf("Pago? (0 = nao, 1 = sim)\n");
    scanf("%d", &insc[pos].pago);
    getchar();

    printf("Inscricao atualizada com sucesso.\n");
}

void remover_inscricao(Inscricao **insc, int *qtd){
    int id;

    if (*qtd == 0 || *insc == NULL) {
        printf("Nenhuma inscricao cadastrada.\n");
        return;
    }

    printf("Digite o ID da inscricao que deseja remover\n");
    scanf("%d", &id);
    getchar();

    int pos = buscar_inscricao_id(*insc, *qtd, id);
    if (pos == -1) {
        printf("Inscricao nao encontrada\n");
        return;
    }

    for (int i = pos; i < (*qtd) - 1; i++) {
        (*insc)[i] = (*insc)[i + 1];
    }

    (*qtd)--;

    if (*qtd == 0) {
        free(*insc);
        *insc = NULL;
        printf("Inscricao removida.\n");
        return;
    }

    Inscricao *temp = (Inscricao*)realloc(*insc, (*qtd) * sizeof(Inscricao));
    if (temp != NULL) *insc = temp;

    printf("Inscricao removida.\n");
}
