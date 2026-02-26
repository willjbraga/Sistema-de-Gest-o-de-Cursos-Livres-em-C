#ifndef CURSO
#define CURSO
typedef struct {
    int codigo;
    char titulo[60];
    float preco;
    int vagas;
} Curso;


void cadastrar_curso(Curso **curso, int *qtd);
void listar_cursos(Curso *curso, int qtd);
void buscar_curso(Curso *curso, int qtd);
int  buscar_curso_codigo(Curso *curso, int qtd, int codigo);
void atualizar_curso(Curso *curso, int qtd);
void remover_curso(Curso **curso, int *qtd);

#endif // CURSO
