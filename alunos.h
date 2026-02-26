#ifndef ALUNOS
#define ALUNOS
typedef struct {
    char cpf[12];
    char nome[60];
    char telefone[12];
} Aluno;

void cadastrar_aluno(Aluno **aluno,int *qtd);
void lista_alunos(Aluno *aluno, int qtd);
void buscar_aluno(Aluno *aluno, int qtd);
int buscar_aluno_cpf(Aluno *aluno, int qtd, char *cpf);
void atualizar_aluno(Aluno * aluno, int qtd);
void remover_aluno(Aluno **aluno, int *qtd);

#endif // ALUNOS
