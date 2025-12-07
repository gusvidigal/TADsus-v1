#ifndef DFlistapaciente
#define DFlistapaciente

#include <stdbool.h>

#include "TADhistorico.h"
#include "TADpaciente.h"

#define REALOCACAO_POR_VEZ 5

// IMPLEMENTAÇÃO DA LISTA: Encadeada ordenada (pelo ID) e com nó cabeça

// Struct da lista
typedef struct {
    Paciente* inicio;
    int tamanho;
} ListaPacientes;

// Pré-cond: Existir espaço na memória
// Pós-cond: Retorna ponteiro da lista criada
ListaPacientes* criarListaPacientes();
// Pré-cond: lista existir
// Pós-cond: retorna o tamanho, ou -1 caso a lista não exista
int qtdePacientes(ListaPacientes* lista);
// Pré-cond: Lista e paciente existem
// Pós-cond: Retorna true se a operação foi um sucesso
bool adicionarPacienteNaLista(ListaPacientes* lista, Paciente* paciente);
// Pré-cond: Lista existir
// Pós-cond: Caso o paciente não exista ou ele tenha sido apagado, retorna true
bool apagarPacienteDaLista(ListaPacientes* lista, char* id);
// Pré-cond: Lista existir
// Pós-cond: Retorna ponteiro para o paciente encontrado
Paciente* obterPaciente(ListaPacientes* lista, char* busca, bool porID);
// Pré-cond: Lista existir
// Pós-cond: Retorna um vetor dinâmico dos pacientes
Paciente** listarPacientes(ListaPacientes* lista);
// Pré-cond: A lista existir
// Pós-cond: Retorna se a lista foi apagada com sucesso
bool deletarListaPacientes(ListaPacientes* lista);

#endif