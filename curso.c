#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "curso.h"

static void tirar_enter(char *s) {
    s[strcspn(s, "\n")] = '\0';
}

static void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int buscar_curso_codigo(Curso *curso, int qtd, int codigo) {
    for (int i = 0; i < qtd; i++) {
        if (curso[i].codigo == codigo) return i;
    }
    return -1;
}

void cadastrar_curso(Curso **curso, int *qtd) {
    Curso novo;
    Curso *temp;
    char op = 's';

    while (op == 's' || op == 'S') {

        printf("\nDigite o codigo do curso:\n");
        scanf("%d", &novo.codigo);
        limpar_buffer();

        if (buscar_curso_codigo(*curso, *qtd, novo.codigo) != -1) {
            printf("Codigo ja cadastrado.\n");
            printf("Deseja tentar cadastrar outro curso? (s/n): ");
            scanf(" %c", &op);
            limpar_buffer();
            continue;
        }

        printf("Digite o titulo do curso:\n");
        fgets(novo.titulo, sizeof(novo.titulo), stdin);
        tirar_enter(novo.titulo);

        printf("Digite o preco do curso:\n");
        scanf("%f", &novo.preco);
        limpar_buffer();

        printf("Digite a quantidade de vagas:\n");
        scanf("%d", &novo.vagas);
        limpar_buffer();

        temp = (Curso*)realloc(*curso, (*qtd + 1) * sizeof(Curso));
        if (temp == NULL) {
            printf("Falha ao alocar/realocar memoria.\n");
            return;
        }

        *curso = temp;
        (*curso)[*qtd] = novo;
        (*qtd)++;

        printf("Deseja cadastrar outro curso em sequencia? (s/n): ");
        scanf(" %c", &op);
        limpar_buffer();
    }
}

void listar_cursos(Curso *curso, int qtd) {
    if (qtd == 0 || curso == NULL) {
        printf("Nenhum curso cadastrado.\n");
        return;
    }

    for (int i = 0; i < qtd; i++) {
        printf("\n-- Curso %d --\n", i + 1);
        printf("Codigo: %d\n", curso[i].codigo);
        printf("Titulo: %s\n", curso[i].titulo);
        printf("Preco: %.2f\n", curso[i].preco);
        printf("Vagas: %d\n", curso[i].vagas);
    }
}

void buscar_curso(Curso *curso, int qtd) {
    int codigo;

    if (qtd == 0 || curso == NULL) {
        printf("Nenhum curso cadastrado.\n");
        return;
    }

    printf("Digite o codigo do curso:\n");
    scanf("%d", &codigo);
    limpar_buffer();

    int id_curso = buscar_curso_codigo(curso, qtd, codigo);
    if (id_curso == -1) {
        printf("Curso nao encontrado.\n");
        return;
    }

    printf("\n-- Curso encontrado --\n");
    printf("Codigo: %d\n", curso[id_curso].codigo);
    printf("Titulo: %s\n", curso[id_curso].titulo);
    printf("Preco: %.2f\n", curso[id_curso].preco);
    printf("Vagas: %d\n", curso[id_curso].vagas);
}

void atualizar_curso(Curso *curso, int qtd) {
    int codigo;

    if (qtd == 0 || curso == NULL) {
        printf("Nenhum curso cadastrado.\n");
        return;
    }

    printf("Digite o codigo do curso que deseja atualizar:\n");
    scanf("%d", &codigo);
    limpar_buffer();

    int id_curso = buscar_curso_codigo(curso, qtd, codigo);
    if (id_curso == -1) {
        printf("Curso nao encontrado.\n");
        return;
    }

    printf("\nAtualizando curso: %s\n", curso[id_curso].titulo);

    printf("Digite o novo titulo:\n");
    fgets(curso[id_curso].titulo, sizeof(curso[id_curso].titulo), stdin);
    tirar_enter(curso[id_curso].titulo);

    printf("Digite o novo preco:\n");
    scanf("%f", &curso[id_curso].preco);
    limpar_buffer();

    printf("Digite a nova quantidade de vagas:\n");
    scanf("%d", &curso[id_curso].vagas);
    limpar_buffer();

    printf("Curso atualizado com sucesso.\n");
}

void remover_curso(Curso **curso, int *qtd) {
    int codigo;

    if (*qtd == 0 || *curso == NULL) {
        printf("Nenhum curso cadastrado.\n");
        return;
    }

    printf("Digite o codigo do curso que deseja remover:\n");
    scanf("%d", &codigo);
    limpar_buffer();

    int id_curso = buscar_curso_codigo(*curso, *qtd, codigo);
    if (id_curso == -1) {
        printf("Curso nao encontrado.\n");
        return;
    }

    for (int i = id_curso; i < (*qtd) - 1; i++) {
        (*curso)[i] = (*curso)[i + 1];
    }

    (*qtd)--;

    if (*qtd == 0) {
        free(*curso);
        *curso = NULL;
        printf("Curso removido.\n");
        return;
    }

    Curso *temp = (Curso*)realloc(*curso, (*qtd) * sizeof(Curso));
    if (temp != NULL) *curso = temp;

    printf("Curso removido.\n");
}
