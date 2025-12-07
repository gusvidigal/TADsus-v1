#include "TADpaciente.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TADhistorico.h"

// Pré-cond: espaço na memória
// Pós-cond: cria o paciente e retorna ponteiro para ele
Paciente* criarPaciente(char* nome, char* id) {
    Paciente* paciente = (Paciente*)calloc(1, sizeof(Paciente));
    if (!paciente) return NULL;
    Historico* historico = criarHistorico();
    if (!historico) {
        free(paciente);
        return NULL;
    }
    // Copia dados
    strcpy(paciente->id, id);
    strcpy(paciente->nome, nome);
    paciente->historico = historico;
    return paciente;
}
// Pré-cond: paciente existir
// Pós-cond: retorna o nome ou ponteiro para NULL
char* obterNome(Paciente* paciente) {
    if (!paciente) return NULL;
    return paciente->nome;
}
// Pré-cond: paciente existir
// Pós-cond: retorna o id ou ponteiro para NULL
char* obterId(Paciente* paciente) {
    if (!paciente) return NULL;
    return paciente->id;
}
// Pré-cond: paciente existir
// Pós-cond: retorna o histórico do paciente ou ponteiro para NULL
Historico* obterHistorico(Paciente* paciente) {
    if (!paciente) return NULL;
    return paciente->historico;
};
// Pré-cond: histórico e paciente existirem
// Pós-cond: retorna verdadeiro se conseguiu atribuir
bool atribuirHistorico(Paciente* paciente, Historico* historico) {
    if (!paciente || !historico) return false;
    //Desaloca histórico antigo
    if(paciente->historico) free(paciente->historico);
    paciente->historico = historico;
    return true;
}
// Pré-cond: o paciente original existir
// Pós-cond: retorna um ponteiro com a copia do paciente (ou NULL caso não exista)
Paciente* copiarPaciente(Paciente* original) {
    if (!original) return NULL;
    Paciente* paciente = criarPaciente(original->nome, original->id);
    return paciente;
};
// Pré-cond: paciente existir
// Pós-cond: retorna true caso consiga apagar
bool apagarPaciente(Paciente* paciente) {
    if (!paciente) return false;
    deletarHistorico(paciente->historico);
    free(paciente);
    return true;
}
