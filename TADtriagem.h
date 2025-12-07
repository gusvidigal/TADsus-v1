#ifndef DFtriagem
#define DFtriagem

#include <stdbool.h>

#include "TADlistapaciente.h"
#include "TADpaciente.h"

#define MAX_TRIAGEM 20

// Struct da triagem
typedef struct {
    Paciente* pacientes[MAX_TRIAGEM];
    int inicio;
    int tamanho;
} Triagem;

// Pré-cond: espaço na memória
// Pós-cond: retorna ponteiro para a fila
Triagem* criarTriagem();
// Pré-cond: fila existe
// Pós-cond: retorna o tamanho da triagem, ou -1 caso ela não existe
int tamanhoTriagem(Triagem* triagem);
// Pré-cond: fila existe
// Pós-cond: retorna true se a fila está cheia
bool triagemCheia(Triagem* triagem);
// Pré-cond: fila existe
// Pós-cond: retorna true se a fila está vazia
bool triagemVazia(Triagem* triagem);
// Pré-cond: fila e paciente existem, fila não está cheia
// Pós-cond: returna true caso a inserção seja um sucesso
bool inserirNaTriagem(Triagem* triagem, Paciente* paciente);
// Pré-cond: a triagem e o paciente existem
// Pós-cond: retorna true se o paciente está na triagem
bool pacienteNaTriagem(Triagem* triagem, Paciente* paciente);
// Pré-cond: fila existe e não está vazia
// Pós-cond: retorna ponteiro do paciente removido
Paciente* removerDoInicio(Triagem* triagem);
// Pré-cond: fila e paciente existem, fila não vazia e paciente na triagem
// Pós-cond: retorna true se a operação foi bem sucedida
bool removerDaTriagem(Triagem* triagem, Paciente* paciente);
// Pré-cond: a fila existe
// Pós-cond: retorna vetor dinâmico dos pacientes
Paciente** mostrarTriagem(Triagem* triagem);
// Pré-cond: a triagem existir
// Pós-cond: retorna true se conseguiu remover a triagem
bool excluirTriagem(Triagem* triagem);

#endif
