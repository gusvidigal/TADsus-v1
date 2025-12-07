#include "TADhistorico.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// IMPLEMENTAÇÃO DO HISTÓRICO: Pilha estática

// Pré-cond: existir espaço na memória
// Pós-cond: retorna o ponteiro para o histórico criado
Historico* criarHistorico() {
    Historico* historico = (Historico*)calloc(1, sizeof(Historico));
    if (!historico) return NULL;
    historico->topo = -1;
    return historico;
}
// Pré-cond: o histórico original deve existir
// Pós-cond: retorna ponteiro para historico copiado
Historico* copiarHistorico(Historico* original) {
    if (!original) return NULL;
    Historico* copia = criarHistorico();
    if (!copia) return NULL;
    // Copia do histórico
    copia->topo = original->topo;
    for (int i = 0; i < MAX_PROCEDIMENTOS; i++) {
        for (int j = 0; j < MAX_TAMANHO_PROCEDIMENTOS + 1; j++) {
            copia->procedimentos[i][j] = original->procedimentos[i][j];
        }
    }
    return copia;
};
// Pré-cond: exisitr o histórico
// Pós-cond: retorna o número de procedimentos do histórico. -1 caso não exista
int qtdeProcedimentos(Historico* historico) {
    if (!historico)
        return -1;
    else
        return historico->topo + 1;
}
// Pré-cond: o histórico existir
// Pós-cond: retorna se o topo do histórico é o último item
bool historicoCheio(Historico* historico) {
    return !historico || historico->topo == MAX_PROCEDIMENTOS - 1;
}
// Pré-cond: o histórico existir
// Pós-cond: retorna se o topo do histórico é -1 (vazio)
bool historicoVazio(Historico* historico) {
    return !historico || historico->topo == -1;
}
// Pré-cond: o histórico não estar cheio/existir
// Pós-cond: retorna se a operação de copiar o procedimento foi feita
bool inserirProcedimento(Historico* historico, char* proc) {
    if (!historico || historico->topo == MAX_PROCEDIMENTOS - 1) return false;
    historico->topo++;
    // Insere o procedimento
    strcpy(historico->procedimentos[historico->topo], proc);
    return true;
}
// Pré-cond: o histórico não estar vazio/existir
// Pós-cond: retorna se foi deletado e armazena o valor no vetor
bool removerProcedimento(Historico* historico, char* copia) {
    if (!historico || historico->topo == -1) return false;
    strcpy(copia, historico->procedimentos[historico->topo]);
    historico->topo--;
    return true;
}
// Pré-cond: o histórico não estar vazio/existir
// Pós-cond: retorna o ponteiro para o procedimento mais recente
char* procedimentoMaisRecente(Historico* historico) {
    if (!historico) return NULL;
    return historico->procedimentos[historico->topo];
}
// Pré-cond: o histórico não estar vazio/existir
// Pós-cond: retorna a matriz dos procedimentos
char (*consultarHistorico(Historico* historico))[MAX_TAMANHO_PROCEDIMENTOS + 1] {
    if (!historico || historico->topo == -1) return NULL;
    return historico->procedimentos;
}
// Pré-cond: histórico existir
// Pós-cond: retorna true caso o histórico seja desalocado
bool deletarHistorico(Historico* historico) {
    if (!historico) return false;
    free(historico);
    return true;
}
