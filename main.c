#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TADhistorico.h"
#include "TADio.h"
#include "TADlistapaciente.h"
#include "TADpaciente.h"
#include "TADtriagem.h"

const char *linha = "---------------";

// INPUTS E STRINGS

// Pré-cond: nenhuma
// Pós-cond: limpa o buffer até o \n ou EOF
void limparBuffer();
// Pré-cond: cópia existir (e ter, no máximo, máximo + 1 caracteres)
// Pós-cond: retorna true se leu um número de caracteres aceitável
bool lerString(char *copia, int maximo);
// Pré-cond: copia existir
// Pós-cond: retorna true se leu um número convertível
bool lerInt(int *copia);
// Pré-cond: nenhuma
// Pós-cond: armazena a string em minúscula no vetor passado
void toLowerCase(char *palavra, char *novaPalavra, int tamanho);

// UTILITÁRIOS

// Pré-cond: pacientes existirem
// Pós-cond: retorna true se o primeiro paciente estiver alfabeticamente antes
bool compPacientes(Paciente *p1, Paciente *p2);
// Pré-cond: lista existir
// Pós-cond: ordena a lista pelos nomes (não é case-sensitive) e retorna se conseguiu
bool quickSort(int tamanho, Paciente **pacientes, int i, int j);
// Pré-cond: nenhuma
// Pós-cond: retorna NULL se o paciente for encontrado
Paciente *solicitarPaciente(ListaPacientes *lista, bool porID);

// FUNÇÕES DO MENU

void C0_listaDeComandos();
void C1_funcionamento();
bool C2_sair(ListaPacientes *lista, Triagem *triagem);
void C3_registrarPaciente(ListaPacientes *lista, Triagem *triagem);
void C4_registrarObito(ListaPacientes *lista, Triagem *triagem);
void C5_listarPacientes(ListaPacientes *lista);
void C6_7_buscarPaciente(ListaPacientes *lista, bool porId);
void C8_inserirNaTriagem(ListaPacientes *lista, Triagem *triagem);
void C9_chamarPaciente(Triagem *triagem);
void C10_mostrarTriagem(Triagem *triagem);
void C11_mostrarHistorico(ListaPacientes *lista);
void C12_adicionarProcedimento(ListaPacientes *lista);
void C13_desfazerProcedimento(ListaPacientes *lista);
// Pré-cond: lista e paciente existirem
// Pós-cond: executa a ação fornecida pelo usuário e retorna se ele saiu do sistema
bool lerComando(ListaPacientes *lista, Triagem *triagem);

int main() {
    printf("Olá! Bem-vindo(a) ao Gerenciamento do Pronto Socorro do SUS.\n");
    // Carregar ou criar novos?
    int comando, erro = 1;
    do {
        printf("%s\n", linha);
        if (erro == 0)
            printf("(X) Comando inválido! Digite 1 para carregar os dados ou 2 para criar novos.\n");
        // Lê o comando
        printf("Digite 1 para carregar os dados em \"%s\" e \"%s\" ou 2 para sobrescrever os dados atuais: ", ARQUIVO_PADRAO_LISTA, ARQUIVO_PADRAO_TRIAGEM);
        erro = (int)lerInt(&comando);
    } while (erro == 0 || (comando != 1 && comando != 2));

    // Carrega os dados
    ListaPacientes *lista;
    Triagem *triagem;
    if (comando == 1) {
        printf("Carregando dados dos arquivos %s e %s...\n", ARQUIVO_PADRAO_LISTA, ARQUIVO_PADRAO_TRIAGEM);
        if (!load(&lista, &triagem)) {
            printf("(X) ERRO ao carregar os dados!\n");
            return 0;
        }
        printf("(V) Os dados foram carregados com sucesso!\n");
    } else {
        // Cria a lista de pacientes
        lista = criarListaPacientes();
        if (!lista) return 0;
        // Cria a triagem
        triagem = criarTriagem();
        if (!triagem) {
            deletarListaPacientes(lista);
            return 0;
        }
    }
    // Imprime o menu
    C0_listaDeComandos();
    // Mostra o menu e aguarda comandos até o usuário sair
    while (lerComando(lista, triagem));
    printf("Sistema desligado!\n");
    return 0;
}

// INPUTS E STRINGS

// Pré-cond: nenhuma
// Pós-cond: limpa o buffer até o \n ou EOF
void limparBuffer() {
    char c;
    while (c != '\n' && c != EOF)
        c = fgetc(stdin);
}
// Pré-cond: cópia existir (e ter, no máximo, máximo + 1 caracteres)
// Pós-cond: retorna true se leu um número de caracteres aceitável
bool lerString(char *copia, int maximo) {
    if (!copia) return false;
    int i, count = 0;
    char c;
    for (i = 0; i < maximo; i++) {
        c = fgetc(stdin);
        // Se chegou no fim do input dentro de maximo
        if (c == '\n' || c == EOF) {
            copia[count] = '\0';
            return true;
        }
        copia[count] = c;
        count++;
    }
    limparBuffer();
    return false;
}
// Pré-cond: copia existir
// Pós-cond: retorna true se leu um número convertível
bool lerInt(int *copia) {
    if (!copia) return NULL;
    int digitos[10], qtde = 0, pot = 1, i;
    bool flag = true;
    char c;
    for (i = 0; i < 9; i++) {
        c = fgetc(stdin);
        if (c == '\n' || c == EOF)
            break;
        else if (c < '0' || c > '9') {
            flag = false;
            break;
        }
        // Adiciona o dígito
        digitos[i] = c - '0';
        qtde++;
    }
    if (flag) {
        if(qtde == 0) return false;
        // Base decimal
        *copia = 0;
        for (i = qtde - 1; i >= 0; i--, pot *= 10)
            *copia += digitos[i] * pot;
        return true;
    }
    limparBuffer();
    return false;
}
// Pré-cond: nenhuma
// Pós-cond: armazena a string em minúscula no vetor passado
void toLowerCase(char *palavra, char *novaPalavra, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        char c = palavra[i];
        if (c >= 'A' && c <= 'Z')
            // Converte para minúscula
            novaPalavra[i] = c + 32;
        else
            novaPalavra[i] = c;
        if (c == '\0')
            break;
    }
}

// UTILITÁRIOS

// Pré-cond: pacientes existirem
// Pós-cond: retorna true se o primeiro paciente estiver alfabeticamente antes
bool compPacientes(Paciente *p1, Paciente *p2) {
    if (!p1 || !p2) return false;
    // Obtém nomes e converte
    char *n1 = obterNome(p1), *n2 = obterNome(p2);
    char n1Lower[MAX_NOME_PACIENTE + 1], n2Lower[MAX_NOME_PACIENTE];
    toLowerCase(n1, n1Lower, MAX_NOME_PACIENTE + 1);
    toLowerCase(n2, n2Lower, MAX_NOME_PACIENTE + 1);
    // Compara os nomes
    int comp = strcmp(n1Lower, n2Lower);
    return comp != 0 ? comp > 0 : strcmp(obterId(p1), obterId(p2));
}
// Pré-cond: lista existir
// Pós-cond: ordena a lista pelos nomes (não é case-sensitive) e retorna se conseguiu
bool quickSort(int tamanho, Paciente **pacientes, int i, int j) {
    if (tamanho <= 1)
        return true;
    else if (!pacientes)
        return false;
    int copyI = i, copyJ = j;
    Paciente *pivo = pacientes[(i + j) / 2];
    // Separa os elementos
    do {
        while (compPacientes(pivo, pacientes[i]))
            i++;
        while (compPacientes(pacientes[j], pivo))
            j--;
        // Realiza a troca
        if (i < j) {
            Paciente *aux = pacientes[i];
            pacientes[i] = pacientes[j];
            pacientes[j] = aux;
        };
    } while (i < j);
    // Separa dentro dos subvetores
    quickSort(i - copyI, pacientes, copyI, i - 1);
    quickSort(copyJ - i, pacientes, i + 1, copyJ);
    return true;
}
// Pré-cond: nenhuma
// Pós-cond: retorna NULL se o paciente não for encontrado
Paciente *solicitarPaciente(ListaPacientes *lista, bool porID) {
    Paciente *paciente;
    if (porID) {
        char id[MAX_ID_PACIENTE + 1];
        printf("Digite o ID do paciente: ");
        lerString(id, MAX_ID_PACIENTE + 1);
        // Procura o paciente
        paciente = obterPaciente(lista, id, true);
    } else {
        char nome[MAX_NOME_PACIENTE + 1];
        printf("Digite o nome do paciente: ");
        lerString(nome, MAX_NOME_PACIENTE + 1);
        paciente = obterPaciente(lista, nome, false);
    }
    if (!paciente) {
        printf("(X) Paciente não encontrado!\n");
        return NULL;
    }
    return paciente;
}

// FUNÇÕES DO MENU

// COMANDO 0 - Impressão do menu
void C0_listaDeComandos() {
    printf(
        "%s\n\
LISTA DE COMANDOS\n\
\n\
- MENU - \n\
[0] Mostrar lista de comandos \n\
[1] Funcionamento | INFORMAÇÕES SOBRE O TRABALHO \n\
[2] Sair \n\
- PACIENTES - \n\
[3] Registrar paciente \n\
[4] Registrar óbito do paciente \n\
[5] Listar pacientes registrados \n\
[6] Buscar paciente por ID \n\
[7] Buscar paciente por nome \n\
- FILA DE ESPERA (TRIAGEM) - \n\
[8] Inserir paciente na triagem \n\
[9] Chamar próximo paciente para atendimento \n\
[10] Mostrar fila de espera \n\
- HISTÓRICO MÉDICO - \n\
[11] Mostrar histórico do paciente \n\
[12] Adicionar procedimento ao histórico médico \n\
[13] Desfazer procedimento do histórico médico \n",
        linha);
}
// COMANDO 1 - Funcionamento do sistema
void C1_funcionamento() {
    printf(
        "%s\n\
Projeto 1: Serviço de atendimento de Emergência Hospitalar\n\
SCC0202 - Algoritmos e Estruturas de Dados I - 2025\n\
\n\
INTEGRANTES:\n\
[16832658] Bruno Dias de Campos Filho: \n\
[16814327] Gustavo Vidigal Schulgin: \n\
[16827777] Pedro Tiago Biffi: \n\
\n\
EXPLICAÇÕES GERAIS \n\
O trabalho contém, ao todo, 5 TADS: Histórico, Paciente, Lista de Pacientes, Triagem (Fila de espera) e IO. A dependência deles é a seguinte: \n\
Histórico - Não tem dependências \n\
Paciente - Extende o histórico \n\
Lista de pacientes - Extende o paciente (que extende o histórico) \n\
Triagem - Extende o paciente e a lista de pacientes \n\
IO - Extende a lista de pacientes e a triagem \n\
\n\
IMPLEMENTAÇÕES \n\
Para o paciente, foi apenas criado um struct com funções. Para o IO, apenas funções. \n\
Para o histórico, foi implementada uma PILHA estática. \n\
Para a lista de pacientes, foi implementada uma LISTA dinâmica ordenada encadeada com nó cabeça. \n\
Para a triagem, foi implementada uma FILA estática circular. \n\
\n\
ALOCAÇÕES DINÂMICAS \n\
Para estruturas pequenas, como os procedimentos (matriz de 10x100) e o vetor de ponteiros da triagem, foram usadas variáveis na Stack. Porém, todas as funções de CRIAR TADs utilizam alocações dinâmicas para alocarem os structs. As funções de consultas (da triagem e da lista de pacientes) também criam alocações dinâmicas para armazenarem os resultados. A liberação dessas 2 memórias fica a cargo do usuário. O código foi checado com valgrind e não obteve vazamentos de memória. \n\
\n\
FUNÇÕES EXTRAS \n\
Apesar de não especificadas no PDF, implementamos funções adicionais que auxiliariam na utilização do menu. Por exemplo, ordenamos por QuickSort a lista de pacientes antes de imprimir (por padrão, ela é ordenada por ID, mas o usuário pode ordenar por nome). ALém disso, para evitar redigitar comandos, o programa entra num while caso o usuário digite um nome/id de paciente ou prescrição com mais caracteres do que devia (esse loop é finalizável digitando '*'). O usuário também pode buscar pacientes por ID ou por NOME e também pode optar por criar um novo registro ou carregar o já existente no arquivo. \n\
\n", linha);
};
// COMANDO 2 - Sair do sistema e salvar
bool C2_sair(ListaPacientes *lista, Triagem *triagem) {
    bool salvar = save(lista, triagem);
    if (!salvar) {
        printf("(X) ERRO ao salvar os dados!\n");
    } else
        printf("(V) Dados salvos corretamente!\n");
    return salvar;
}
// COMANDO 3 - Registrar paciente
void C3_registrarPaciente(ListaPacientes *lista, Triagem *triagem) {
    int erro;
    // Lê o nome do paciente
    char nome[MAX_NOME_PACIENTE + 1];
    erro = 1;
    do {
        if (erro == 0)
            printf("(X) O nome pode ter, no máximo, %d caracteres.\n", MAX_NOME_PACIENTE);
        printf("Digite o nome do paciente a ser adicionado (digite * para sair): ");
        erro = (int)lerString(nome, MAX_NOME_PACIENTE + 1);
    } while (erro == 0);
    if (nome[0] == '*' && nome[1] == '\0') {
        printf("(V) Operação cancelada!\n");
        return;
    }
    // Lê a id do paciente
    char id[MAX_ID_PACIENTE + 1];
    erro = 1;
    do {
        if (erro == 0)
            printf("(X) O ID pode ter, no máximo, %d caracteres.\n", MAX_ID_PACIENTE);
        else if (erro == -1)
            printf("(X) Já existe um paciente com esse ID!\n");
        // Lê e cataloga se tem algum erro
        printf("Digite o ID do paciente (digite * para sair): ");
        if (!lerString(id, MAX_ID_PACIENTE + 1))
            erro = 0;
        else if (obterPaciente(lista, id, true) != NULL)
            erro = -1;
        else
            erro = 1;
    } while (erro != 1);
    if (id[0] == '*' && id[1] == '\0') {
        printf("(V) Operação cancelada!\n");
        return;
    }
    // Registra o paciente
    Paciente *paciente = criarPaciente(nome, id);
    if (!paciente || !adicionarPacienteNaLista(lista, paciente)) return;
    // Finaliza
    printf("(V) Paciente de nome \"%s\" e id \"%s\" adicionado com sucesso!\n", nome, id);
    // Adiciona na fila de espera
    if (triagemCheia(triagem)) {
        printf("(X) A fila está cheia! Não foi possível adicionar o paciente na triagem.\n");
        return;
    }
    bool resultado = inserirNaTriagem(triagem, paciente);
    if (resultado)
        printf("(V) Paciente adicionado na posição %d da fila de espera!\n", tamanhoTriagem(triagem));
    return;
}
// COMANDO 4 - Registrar óbito
void C4_registrarObito(ListaPacientes *lista, Triagem *triagem) {
    // Lê o id do paciente e o retorna
    Paciente *paciente = solicitarPaciente(lista, true);
    if (!paciente) return;
    // Verifica se está na triagem
    if (pacienteNaTriagem(triagem, paciente)) {
        printf("(X) Não foi possível registrar o óbito, pois o paciente está na triagem!\n");
        return;
    }
    apagarPacienteDaLista(lista, obterId(paciente));
    printf("(V) Óbito do paciente \"%s\" registrado!\n", obterNome(paciente));
    return;
}
// COMANDO 5 - Lista pacientes
void C5_listarPacientes(ListaPacientes *lista) {
    // Obtém a lista de pacientes
    Paciente **pacientes = listarPacientes(lista);
    if (!pacientes) {
        printf("(X) Não existem pacientes registrados!\n");
        return;
    }
    // Obtém a forma de ordenação
    int forma, erro = 1;
    do {
        printf("%s\n", linha);
        if (erro == 0)
            printf("Forma inválida!\n");
        printf("Digite 1 para listar por nome ou 2 para listar por id: ");
        erro = (int)lerInt(&forma);
    } while (erro == 0 || (forma != 1 && forma != 2));
    // Ordenação em ordem alfabética de nome
    int tamanho = qtdePacientes(lista);
    if (forma == 1)
        quickSort(tamanho, pacientes, 0, tamanho - 1);
    // Impressão
    for (int i = 0; i < tamanho; i++) {
        Paciente *paciente = pacientes[i];
        printf("%d. Nome: \"%s\"; ID: \"%s\"\n", i + 1, obterNome(paciente), obterId(paciente));
    }
    // Libera a lista
    free(pacientes);
    return;
}
// COMANDO 6/7 - Buscar paciente por ID
void C6_7_buscarPaciente(ListaPacientes *lista, bool porId) {
    // Lê a informação do paciente
    Paciente *paciente = solicitarPaciente(lista, porId);
    if (!paciente) return;
    printf("(V) Paciente encontrado!\n%s\n", linha);
    printf("Nome: \"%s\"; ID: \"%s\"\n", obterNome(paciente), obterId(paciente));
    // Obtém os procedimentos
    Historico *historico = obterHistorico(paciente);
    if (!historico) {
        printf("(X) Um erro ocorreu ao acessar o histórico do paciente.\n");
        return;
    }
    char (*procedimentos)[MAX_TAMANHO_PROCEDIMENTOS + 1] = consultarHistorico(historico);
    if (historicoVazio(historico)) {
        printf("Histórico vazio!\n");
        return;
    }
    printf("Histórico do paciente:\n");
    int qtde = qtdeProcedimentos(historico);
    for (int i = 0; i < qtde; i++)
        printf("[%d] \"%s\"\n", i + 1, procedimentos[i]);
    return;
}
// COMANDO 8 - Insere um paciente no fim da triagem
void C8_inserirNaTriagem(ListaPacientes *lista, Triagem *triagem) {
    if (triagemCheia(triagem)) {
        printf("(X) A fila está cheia! Remova algum paciente antes de inserir outro.\n");
        return;
    }
    Paciente *paciente = solicitarPaciente(lista, true);
    if (!paciente) return;
    if (pacienteNaTriagem(triagem, paciente)) {
        printf("(X) O paciente já está na triagem!\n");
        return;
    }
    if (inserirNaTriagem(triagem, paciente)) {
        printf("(V) Paciente de nome \"%s\" e id \"%s\" adicionado na posição %d da fila de espera!\n", obterNome(paciente), obterId(paciente), tamanhoTriagem(triagem));
        return;
    }
    printf("(X) Um erro ocorreu ao realizar essa ação.\n");
    return;
}
// COMANDO 9 - Chama o paciente e tira da triagem
void C9_chamarPaciente(Triagem *triagem) {
    if (triagemVazia(triagem)) {
        printf("(X) A fila de espera está vazia!\n");
        return;
    }
    Paciente *paciente = removerDoInicio(triagem);
    if (!paciente) {
        printf("(X) O paciente não foi reconhecido.\n");
        return;
    }
    printf("(V) O paciente de nome \"%s\" e id \"%s\" foi chamado!\n", obterNome(paciente), obterId(paciente));
    return;
}
// COMANDO 10 - Mostrar triagem
void C10_mostrarTriagem(Triagem *triagem) {
    // Obtém a lista de pacientes
    Paciente **pacientes = mostrarTriagem(triagem);
    if (!pacientes) {
        printf("(X) Não existem pacientes na triagem!\n");
        return;
    }
    // Impressão
    printf("TRIAGEM (Capacidade de %d pessoas):\n%s\n", MAX_TRIAGEM, linha);
    int tamanho = tamanhoTriagem(triagem);
    for (int i = 0; i < tamanho; i++) {
        if (!pacientes[i]) break;
        Paciente *paciente = pacientes[i];
        printf("[%d] Nome: \"%s\"; ID: \"%s\"\n", i + 1, obterNome(paciente), obterId(paciente));
    }
    // Libera a lista
    free(pacientes);
    return;
}
// COMANDO 11 - Mostrar histórico
void C11_mostrarHistorico(ListaPacientes *lista) {
    Paciente *paciente = solicitarPaciente(lista, true);
    if (!paciente) return;
    Historico *historico = obterHistorico(paciente);
    if (!historico) {
        printf("(X) Histórico não encontrado.\n");
        return;
    }
    // Obtém os procedimentos
    char (*procedimentos)[MAX_TAMANHO_PROCEDIMENTOS + 1] = consultarHistorico(historico);
    if (historicoVazio(historico)) {
        printf("(X) Histórico vazio!\n");
        return;
    }
    printf("Histórico do paciente \"%s\":\n", obterNome(paciente));
    int qtde = qtdeProcedimentos(historico);
    for (int i = 0; i < qtde; i++)
        printf("[%d] \"%s\"\n", i + 1, procedimentos[i]);
}
// COMANDO 12 - Adicionar procedimento
void C12_adicionarProcedimento(ListaPacientes *lista) {
    // Paciente
    Paciente *paciente = solicitarPaciente(lista, true);
    if (!paciente) return;
    Historico *historico = obterHistorico(paciente);
    if (!historico) {
        printf("(X) Histórico não encontrado.\n");
        return;
    }
    if (historicoCheio(historico)) {
        printf("(X) O histórico do paciente está cheio!\n");
        return;
    }
    // Lê o procedimento
    char prescricao[MAX_TAMANHO_PROCEDIMENTOS + 1];
    int erro = 1;
    do {
        if (erro == 0)
            printf("(X) O procedimento pode ter, no máximo, %d caracteres.\n", MAX_TAMANHO_PROCEDIMENTOS);
        printf("Digite o procedimento a ser adicionado (digite * para sair): ");
        erro = (int)lerString(prescricao, MAX_TAMANHO_PROCEDIMENTOS + 1);
    } while (erro == 0);
    if (prescricao[0] == '*' && prescricao[1] == '\0') {
        printf("(V) Operação cancelada!\n");
        return;
    }
    if (inserirProcedimento(historico, prescricao)) {
        printf("(V) Procedimento \"%s\" adicionado ao paciente \"%s\"!\n", prescricao, obterNome(paciente));
        return;
    }
    printf("(X) Um erro ocorreu ao adicionar o procedimento.");
    return;
}
// COMANDO 13 - Remover procedimento
void C13_desfazerProcedimento(ListaPacientes *lista) {
    // Paciente
    Paciente *paciente = solicitarPaciente(lista, true);
    if (!paciente) return;
    Historico *historico = obterHistorico(paciente);
    if (!historico) {
        printf("(X) Histórico não encontrado.\n");
        return;
    }
    if (historicoVazio(historico)) {
        printf("(X) O histórico do paciente está vazio!\n");
        return;
    }
    // Remove o procedimento
    char procedimento[MAX_TAMANHO_PROCEDIMENTOS + 1];
    if (removerProcedimento(historico, procedimento)) {
        printf("(V) O procedimento \"%s\" foi removido do paciente \"%s\"!\n", procedimento, obterNome(paciente));
        return;
    }
    printf("(X) Um erro ocorreu ao remover o procedimento.\n");
    return;
}
// Pré-cond: lista e paciente existirem
// Pós-cond: executa a ação fornecida pelo usuário e retorna se ele saiu do sistema
bool lerComando(ListaPacientes *lista, Triagem *triagem) {
    if (!lista || !triagem) {
        printf("A lista ou a triagem não foram criadas!\n");
        return false;
    }
    int comando, erro = 1;
    //  Recebe comando do usuário
    bool resultado = true;
    do {
        printf("%s\n", linha);
        if (erro == 0)
            printf("Comando inválido! Digite 0 para ver a lista de comandos.\n");
        // Lê o comando
        printf("Digite um comando: ");
        erro = (int)lerInt(&comando);
    } while (erro == 0 || comando < -1 || comando > 13);
    // Executa os comandos
    switch (comando) {
        case -1:
            break;
        case 0:
            C0_listaDeComandos();
            break;
        case 1:
            C1_funcionamento(lista, triagem);
            break;
        case 2:
            resultado = !C2_sair(lista, triagem);
            break;
        case 3:
            C3_registrarPaciente(lista, triagem);
            break;
        case 4:
            C4_registrarObito(lista, triagem);
            break;
        case 5:
            C5_listarPacientes(lista);
            break;
        case 6:
            C6_7_buscarPaciente(lista, true);
            break;
        case 7:
            C6_7_buscarPaciente(lista, false);
            break;
        case 8:
            C8_inserirNaTriagem(lista, triagem);
            break;
        case 9:
            C9_chamarPaciente(triagem);
            break;
        case 10:
            C10_mostrarTriagem(triagem);
            break;
        case 11:
            C11_mostrarHistorico(lista);
            break;
        case 12:
            C12_adicionarProcedimento(lista);
            break;
        case 13:
            C13_desfazerProcedimento(lista);
            break;
    }
    // Resultado será false caso c8_sair() retornar true
    return resultado;
}