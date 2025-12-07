#ifndef DFhistorico
#define DFhistorico

#include <stdbool.h>

#define MAX_PROCEDIMENTOS 10
#define MAX_TAMANHO_PROCEDIMENTOS 100

// IMPLEMENTAÇÃO DO HISTÓRICO: Pilha estática

// Struct do histórico
typedef struct {
    char procedimentos[MAX_PROCEDIMENTOS][MAX_TAMANHO_PROCEDIMENTOS + 1];
    int topo;
} Historico;

// Pré-cond: existir espaço na memória
// Pós-cond: retorna o ponteiro para o histórico criado
Historico* criarHistorico();
// Pré-cond: o histórico original deve existir
// Pós-cond: retorna ponteiro para historico copiado
Historico* copiarHistorico(Historico* original);
// Pré-cond: exisitr o histórico
// Pós-cond: retorna o número de procedimentos do histórico. -1 caso não exista
int qtdeProcedimentos(Historico* historico);
// Pré-cond: o histórico existir
// Pós-cond: retorna se o topo do histórico é o último item
bool historicoCheio(Historico* historico);
// Pré-cond: o histórico existir
// Pós-cond: retorna se o topo do histórico é -1 (vazio)
bool historicoVazio(Historico* historico);
// Pré-cond: o histórico não estar cheio/existir
// Pós-cond: retorna se a operação de copiar o procedimento foi feita
bool inserirProcedimento(Historico* historico, char* proc);
// Pré-cond: o histórico não estar vazio/existir
// Pós-cond: retorna se foi deletado e armazena o valor no vetor
bool removerProcedimento(Historico* historico, char* copia);
// Pré-cond: o histórico não estar vazio/existir
// Pós-cond: retorna o ponteiro para o procedimento mais recente
char* procedimentoMaisRecente(Historico* historico);
// Pré-cond: o histórico não estar vazio/existir
// Pós-cond: retorna uma matriz dos procedimentos
char (*consultarHistorico(Historico* historico))[MAX_TAMANHO_PROCEDIMENTOS + 1];
// Pré-cond: histórico existir
// Pós-cond: retorna true caso o histórico seja desalocado
bool deletarHistorico(Historico* historico);

#endif