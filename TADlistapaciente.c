#include "TADlistapaciente.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TADhistorico.h"
#include "TADpaciente.h"

// IMPLEMENTAÇÃO DA LISTA: Encadeada ordenada (pelo ID) e com nó cabeça

// Pré-cond: Existir espaço na memória
// Pós-cond: Retorna ponteiro da lista criada
ListaPacientes* criarListaPacientes() {
    ListaPacientes* lista = (ListaPacientes*)calloc(1, sizeof(ListaPacientes));
    if (!lista) return NULL;
    // Cria nó cabeça
    Paciente* cabeca = (Paciente*)calloc(1, sizeof(Paciente));
    if (!cabeca) {
        free(lista);
        return NULL;
    }
    cabeca->prox = NULL;
    lista->inicio = cabeca;
    lista->tamanho = 0;
    return lista;
}
// Pré-cond: lista existir
// Pós-cond: retorna o tamanho, ou -1 caso a lista não exista
int qtdePacientes(ListaPacientes* lista) {
    if (!lista) return -1;
    return lista->tamanho;
};
// Pré-cond: Lista e paciente existem
// Pós-cond: Retorna true se a operação foi um sucesso
bool adicionarPacienteNaLista(ListaPacientes* lista, Paciente* paciente) {
    if (!lista || !paciente) return false;
    Paciente* atual = lista->inicio;
    // Procura ponto de inserção
    while (atual->prox != NULL && strcmp(atual->prox->id, paciente->id) < 0)
        atual = atual->prox;
    // Atualiza os ponteiros
    paciente->prox = atual->prox;
    atual->prox = paciente;
    lista->tamanho++;
    return true;
}
// Pré-cond: Lista existir
// Pós-cond: Caso o paciente não exista ou ele tenha sido apagado, retorna true
bool apagarPacienteDaLista(ListaPacientes* lista, char* id) {
    if (!lista) return false;
    Paciente* atual = lista->inicio;
    while (atual->prox != NULL && strcmp(atual->prox->id, id) <= 0) {
        // Encontrou o elemento
        if (strcmp(atual->prox->id, id) == 0) {
            // Apaga o paciente
            Paciente* paciente = atual->prox;
            lista->tamanho--;
            atual->prox = atual->prox->prox;
            apagarPaciente(paciente);
            return true;
        }
        atual = atual->prox;
    }
    // Se iterou e não achou
    return true;
}
// Pré-cond: Lista existir
// Pós-cond: Retorna ponteiro para o paciente encontrado
Paciente* obterPaciente(ListaPacientes* lista, char* busca, bool porID) {
    if (!lista) return NULL;
    Paciente* atual = lista->inicio->prox;
    // Enquanto o atual não for nulo e o id for menor
    // Por ID - busca O((n+1)/2) em média, já que paramos caso o ID passe de busca
    if (porID) {
        while (atual != NULL && strcmp(atual->id, busca) <= 0) {
            if (strcmp(atual->id, busca) == 0)
                return atual;
            atual = atual->prox;
        }
        // Por nome - busca O(n), já que não temos uma lista ordenada por nome
    } else {
        while (atual != NULL) {
            if (strcmp(atual->nome, busca) == 0)
                return atual;
            atual = atual->prox;
        }
    }
    return NULL;
}
// Pré-cond: Lista existir
// Pós-cond: Retorna um vetor dinâmico dos pacientes
Paciente** listarPacientes(ListaPacientes* lista) {
    if (!lista || lista->tamanho == 0) return NULL;
    // Aloca um vetor para armazenar os ponteiros
    Paciente** pacientes = (Paciente**)malloc(sizeof(Paciente*) * (lista->tamanho));
    if (!pacientes) return NULL;
    // Armazena
    Paciente* atual = lista->inicio->prox;
    for (int i = 0; i < lista->tamanho && atual != NULL; i++) {
        pacientes[i] = atual;
        atual = atual->prox;
    }
    return pacientes;
}
// Pré-cond: A lista existir
// Pós-cond: Retorna se a lista foi apagada com sucesso
bool deletarListaPacientes(ListaPacientes* lista) {
    if (!lista) return false;
    Paciente* atual = lista->inicio->prox;
    while (atual != NULL) {
        Paciente* temp = atual->prox;
        // Desaloca o paciente atual
        apagarPaciente(atual);
        atual = temp;
    }
    //Cabeça
    free(lista->inicio);
    free(lista);
    return true;
}