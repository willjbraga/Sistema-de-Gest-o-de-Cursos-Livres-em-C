#ifndef INSCRICAO
#define INSCRICAO

#include "alunos.h"
#include "curso.h"

typedef struct {
    int id;
    char cpfAluno[15];
    int codCurso;
    char data[11];
    int pago;
} Inscricao;


void cadastrar_inscricao(Inscricao **insc, int *qtd, Aluno *aluno, int qtd_aluno, Curso *curso, int qtd_curso);
void listar_inscricoes(Inscricao *insc, int qtd);
void buscar_inscricao(Inscricao *insc, int qtd);
int buscar_inscricao_id(Inscricao *insc, int qtd, int id);
void atualizar_inscricao(Inscricao *insc, int qtd);
void remover_inscricao(Inscricao **insc, int *qtd);

#endif // INSCRICAO
