#include "TADtriagem.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "TADlistapaciente.h"
#include "TADpaciente.h"

// IMPLEMENTAÇÃO DA TRIAGEM: Fila sequencial circular

// Pré-cond: espaço na memória
// Pós-cond: retorna ponteiro para a fila
Triagem* criarTriagem() {
    Triagem* triagem = (Triagem*)malloc(sizeof(Triagem));
    if (!triagem) return NULL;
    triagem->inicio = 0;
    triagem->tamanho = 0;
    return triagem;
}
// Pré-cond: fila existe
// Pós-cond: retorna o tamanho da triagem, ou -1 caso ela não existe
int tamanhoTriagem(Triagem* triagem) {
    if (!triagem) return -1;
    return triagem->tamanho;
}
// Pré-cond: fila existe
// Pós-cond: retorna true se a fila está cheia
bool triagemCheia(Triagem* triagem) {
    return !triagem || triagem->tamanho == MAX_TRIAGEM;
}
// Pré-cond: fila existe
// Pós-cond: retorna true se a fila está vazia
bool triagemVazia(Triagem* triagem) {
    return !triagem || triagem->tamanho == 0;
}
// Pré-cond: fila e paciente existem, fila não está cheia
// Pós-cond: returna true caso a inserção seja um sucesso
bool inserirNaTriagem(Triagem* triagem, Paciente* paciente) {
    if (!triagem || !paciente || triagem->tamanho == MAX_TRIAGEM) return false;
    triagem->pacientes[(triagem->inicio + triagem->tamanho) % MAX_TRIAGEM] = paciente;
    triagem->tamanho++;
    return true;
}
// Pré-cond: a triagem e o paciente existem
// Pós-cond: retorna true se o paciente está na triagem
bool pacienteNaTriagem(Triagem* triagem, Paciente* paciente) {
    if (!triagem || !paciente) return false;
    int inicio = triagem->inicio, fim = (inicio + triagem->tamanho) % MAX_TRIAGEM;
    for (int i = 0, j = inicio; i < triagem->tamanho; i++, j = (j + 1) % MAX_TRIAGEM) {
        if (triagem->pacientes[j] == paciente)
            return true;
    }
    return false;
}
// Pré-cond: fila existe e não está vazia
// Pós-cond: retorna ponteiro do paciente removido
Paciente* removerDoInicio(Triagem* triagem) {
    if (!triagem || triagem->tamanho == 0) return NULL;
    Paciente* paciente = triagem->pacientes[triagem->inicio];
    triagem->inicio = (triagem->inicio + 1) % MAX_TRIAGEM;
    triagem->tamanho--;
    return paciente;
}
// Pré-cond: fila e paciente existem, fila não vazia e paciente na triagem
// Pós-cond: retorna true se a operação foi bem sucedida
bool removerDaTriagem(Triagem* triagem, Paciente* paciente) {
    if (!triagem || !paciente || triagem->tamanho == 0 || pacienteNaTriagem(triagem, paciente))
        return false;
    int i, j, k;
    int inicio = triagem->inicio, fim = (inicio + triagem->tamanho) % MAX_TRIAGEM;
    for (i = 0, j = inicio; i < triagem->tamanho; i++, j = (j + 1) % MAX_TRIAGEM) {
        if (triagem->pacientes[j] == paciente) {
            // Desloca os elementos 1 para frente
            for (k = j; k != fim; k = (k + 1) % MAX_TRIAGEM)
                triagem->pacientes[k] = triagem->pacientes[(k + 1) % MAX_TRIAGEM];
            triagem->tamanho--;
            return true;
        }
    }
    return false;
}
// Pré-cond: a fila existe
// Pós-cond: retorna vetor dinâmico dos pacientes
Paciente** mostrarTriagem(Triagem* triagem) {
    if (!triagem || triagem->tamanho == 0) return NULL;
    Paciente** pacientes = (Paciente**)malloc(sizeof(Paciente*) * (triagem->tamanho));
    if (!pacientes) return NULL;
    for (int i = 0, j = triagem->inicio; i < triagem->tamanho; i++, j = (j + 1) % MAX_TRIAGEM)
        pacientes[i] = triagem->pacientes[j];
    return pacientes;
}
// Pré-cond: a triagem existir
// Pós-cond: retorna true se conseguiu remover a triagem
bool excluirTriagem(Triagem* triagem) {
    if (!triagem) return false;
    free(triagem);
    return true;
}