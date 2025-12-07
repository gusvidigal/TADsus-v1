#ifndef DFpaciente
#define DFpaciente

#include <stdbool.h>

#include "TADhistorico.h"

#define MAX_NOME_PACIENTE 100
#define MAX_ID_PACIENTE 20

// Struct do paciente
typedef struct Paciente_ {
    char id[MAX_ID_PACIENTE + 1];
    char nome[MAX_NOME_PACIENTE + 1];
    Historico* historico;
    struct Paciente_* prox;
} Paciente;

// Pré-cond: espaço na memória
// Pós-cond: cria o paciente e retorna ponteiro para ele
Paciente* criarPaciente(char* nome, char* id);
// Pré-cond: paciente existir
// Pós-cond: retorna o nome ou ponteiro para NULL
char* obterNome(Paciente* paciente);
// Pré-cond: paciente existir
// Pós-cond: retorna o id ou ponteiro para NULL
char* obterId(Paciente* paciente);
// Pré-cond: paciente existir
// Pós-cond: retorna o histórico do paciente ou ponteiro para NULL
Historico* obterHistorico(Paciente* paciente);
// Pré-cond: Histórico e paciente existirem
// Pós-cond: retorna verdadeiro se conseguiu atribuir
bool atribuirHistorico(Paciente* paciente, Historico* historico);
// Pré-cond: o paciente original existir
// Pós-cond: retorna um ponteiro com a copia do paciente (ou NULL caso não exista)
Paciente* copiarPaciente(Paciente* original);
// Pré-cond: paciente existir
// Pós-cond: retorna true caso consiga apagar
bool apagarPaciente(Paciente* paciente);

#endif