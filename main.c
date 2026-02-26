#include <stdio.h>
#include <stdlib.h>
#include "alunos.h"
#include "curso.h"
#include "menu.h"

int main()
{
    Aluno *aluno = NULL;
    int qtd_aluno = 0;
    Curso *curso = NULL;
    int qtd_curso = 0;

    int escolha;
    escolha = menu_principal();

    FILE *faluno = fopen("alunos.bin", "r+b");
    if (faluno == NULL) {
        faluno = fopen("alunos.bin", "w+b");
    }

    if (faluno == NULL){
        printf("Erro na abertura do arquivo aluno.\n");
        exit(1);
    }

    FILE *fcurso = fopen("cursos.bin", "r+b");
    if (fcurso == NULL) {
        fcurso = fopen("cursos.bin", "w+b");
    }

    if (fcurso == NULL){
        printf("Erro na abertura do arquivo curso.\n");
        exit(1);
    }

    fseek(faluno, 0, SEEK_END);
    qtd_aluno = (int)(ftell(faluno) / (long)sizeof(Aluno));
    rewind(faluno);

    if (qtd_aluno > 0) {
        aluno = malloc(qtd_aluno * sizeof *aluno);
        fread(aluno, sizeof *aluno, qtd_aluno, faluno);
    } else {
        aluno = NULL;
    }

    fseek(fcurso, 0, SEEK_END);
    qtd_curso= (int)(ftell(fcurso) / (long)sizeof(Curso));
    rewind(fcurso);

    if (qtd_curso > 0) {
        curso = malloc(qtd_curso * sizeof *curso);
        fread(curso, sizeof *curso, qtd_curso, fcurso);
    } else {
        curso = NULL;
    }


    while(escolha != 0){
        if (escolha == 1){
            int subescolha = menu_alunos();
            switch(subescolha){
                case 1: cadastrar_aluno(&aluno, &qtd_aluno); break;
                case 2: lista_alunos(aluno, qtd_aluno); break;
                case 3: buscar_aluno(aluno, qtd_aluno); break;
                case 4: atualizar_aluno(aluno, qtd_aluno); break;
                case 5: remover_aluno(&aluno, &qtd_aluno); break;
                case 0: break;
                default: printf("Opcao invalida\n"); break;
            }
        }
        else if (escolha == 2){
            int subescolha = menu_cursos();
            switch(subescolha){
                case 1: cadastrar_curso(&curso, &qtd_curso); break;
                case 2: listar_cursos(curso, qtd_curso); break;
                case 3: buscar_curso(curso, qtd_curso); break;
                case 4: atualizar_curso(curso, qtd_curso); break;
                case 5: remover_curso(&curso, &qtd_curso); break;
                case 0: break;
                default: printf("Opcao invalida\n"); break;
            }
        }
        else{
            printf("Escolha invalida\n");
        }
        escolha = menu_principal();
    }

    faluno = freopen("alunos.bin", "wb", faluno);
    fcurso = freopen("cursos.bin", "wb", fcurso);

    if (!faluno || !fcurso) {
        printf("Erro ao salvar arquivos.\n");
        exit(1);
    }

    if (qtd_aluno > 0) fwrite(aluno, sizeof *aluno, qtd_aluno, faluno);
    if (qtd_curso > 0) fwrite(curso, sizeof *curso, qtd_curso, fcurso);

    fclose(faluno);
    fclose(fcurso);

    free(aluno);
    free(curso);

    return 0;
 }
