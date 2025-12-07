#include "TADio.h"

#include <stdio.h>
#include <stdlib.h>

#include "TADhistorico.h"
#include "TADlistapaciente.h"
#include "TADpaciente.h"
#include "TADtriagem.h"

// Pré-cond: lista e triagem existirem
// Pós-cond: retorna true caso salvou
bool save(ListaPacientes *lista, Triagem *triagem) {
    FILE *f;
    Paciente **pacientes;
    Historico *historico;
    char *id;
    int i, tam;

    // Salva a triagem
    f = fopen(ARQUIVO_PADRAO_TRIAGEM, "wb");
    if (!f) return false;
    pacientes = mostrarTriagem(triagem);
    // NUMERO DE PACIENTES NA TRIAGEM
    tam = tamanhoTriagem(triagem);
    fwrite(&tam, sizeof(int), 1, f);
    printf("[IO] Salvando %d pacientes da triagem em %s...\n", tam, ARQUIVO_PADRAO_TRIAGEM);
    // TRIAGEM
    for (i = 0; i < tam; i++) {
        // Salva o ID
        id = obterId(pacientes[i]);
        fwrite(id, sizeof(char) * (MAX_ID_PACIENTE + 1), 1, f);
    }
    // Deleta e desaloca
    excluirTriagem(triagem);
    free(pacientes);
    fclose(f);
    printf("[IO] Salvamento da triagem concluído!\n");

    // Salva a lista
    f = fopen(ARQUIVO_PADRAO_LISTA, "wb");
    if (!f) return false;
    pacientes = listarPacientes(lista);
    // NUMERO DE PACIENTES
    tam = qtdePacientes(lista);
    fwrite(&tam, sizeof(int), 1, f);
    printf("[IO] Salvando %d pacientes da lista em %s...\n", tam, ARQUIVO_PADRAO_LISTA);
    // PACIENTES
    historico = obterHistorico(pacientes[0]);
    for (i = 0; i < tam; i++) {
        historico = obterHistorico(pacientes[i]);
        fwrite(historico, sizeof(Historico), 1, f);
        fwrite(pacientes[i], sizeof(Paciente), 1, f);
    }
    // Deleta e desaloca
    deletarListaPacientes(lista);
    free(pacientes);
    fclose(f);
    printf("[IO] Salvamento da lista concluído!\n");

    return true;
}
// Pré-cond: lista e triagem existirem
// Pós-cond: retorna true caso carregou
bool load(ListaPacientes **lista, Triagem **triagem) {
    FILE *f;
    Paciente *paciente, *p;
    Historico *historico, *h;
    char *id;
    int i, tam;

    // Lê a lista
    f = fopen("PACIENTES.bin", "rb");
    if (!f) return false;
    *lista = criarListaPacientes();
    *triagem = criarTriagem();
    // NUMERO DE PACIENTES
    fread(&tam, sizeof(int), 1, f);
    printf("[IO] Lendo %d pacientes em %s...\n", tam, ARQUIVO_PADRAO_LISTA);
    // PACIENTES
    historico = (Historico *)malloc(sizeof(Historico));
    if (!historico) return false;
    paciente = (Paciente *)malloc(sizeof(Paciente));
    if (!paciente) {
        free(historico);
        return false;
    }
    for (i = 0; i < tam; i++) {
        fread(historico, sizeof(Historico), 1, f);
        fread(paciente, sizeof(Paciente), 1, f);
        h = copiarHistorico(historico);
        p = copiarPaciente(paciente);
        atribuirHistorico(p, h);
        adicionarPacienteNaLista(*lista, p);
    }
    // Desalocações
    free(historico);
    free(paciente);
    fclose(f);
    printf("[IO] Carregamento da lista concluído!\n");

    // Lê a triagem
    f = fopen("TRIAGEM.bin", "rb");
    if (!f) return false;
    // NUMERO DE PACIENTES
    fread(&tam, sizeof(int), 1, f);
    printf("[IO] Lendo %d pacientes na triagem em %s...\n", tam, ARQUIVO_PADRAO_TRIAGEM);
    // PACIENTES
    id = (char *)malloc(sizeof(char) * (MAX_ID_PACIENTE + 1));
    if (!id) return false;
    for (i = 0; i < tam; i++) {
        fread(id, sizeof(char) * (MAX_ID_PACIENTE + 1), 1, f);
        paciente = obterPaciente(*lista, id, true);
        inserirNaTriagem(*triagem, paciente);
    }
    free(id);
    fclose(f);
    printf("[IO] Carregamento da triagem concluído!\n");

    return true;
}