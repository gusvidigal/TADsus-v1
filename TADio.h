#ifndef DFio
#define DFio

#include <stdio.h>

#include "TADhistorico.h"
#include "TADlistapaciente.h"
#include "TADpaciente.h"
#include "TADtriagem.h"

#define ARQUIVO_PADRAO_TRIAGEM "TRIAGEM.bin"
#define ARQUIVO_PADRAO_LISTA "PACIENTES.bin"

// Pré-cond: lista e triagem existirem
// Pós-cond: retorna true caso salvou
bool save(ListaPacientes *lista, Triagem *triagem);
// Pré-cond: lista e triagem existirem
// Pós-cond: retorna true caso carregou
bool load(ListaPacientes **lista, Triagem **triagem);
#endif