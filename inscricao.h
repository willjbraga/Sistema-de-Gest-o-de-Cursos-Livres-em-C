#ifndef INSCRICAO
#define INSCRICAO
typedef struct {
    int id;            // unico (ou gere sequencial)
    char cpfAluno[15]; // referencia Aluno.cpf
    int codCurso;      // referencia Curso.codigo
    char data[11];     // "DD/MM/AAAA"
    int pago;          // 0 = nao, 1 = sim
} Inscricao;
#endif // INSCRICAO
