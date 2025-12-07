Projeto 1: Serviço de atendimento de Emergência Hospitalar
SCC0202 - Algoritmos e Estruturas de Dados I - 2025

INTEGRANTES:
[16832658] Bruno Dias de Campos Filho
[16814327] Gustavo Vidigal Schulgin
[16827777] Pedro Tiago Biffi



EXECUÇÃO DO PROGRAMA:
Para apenas compilar: Utilize o comando "Make reset" no terminal Linux.
Para apenas executar: Utilize o comando "Make run" no terminal Linux.
(!) Para compilar e executar: O comando "Make reboot" executa os dois comandos anteriores.

TESTES:
Para testar o programa, já populamos os arquivos PACIENTES.bin e TRIAGEM.bin. Mas fique à vontade para sobrescrevê-los ou criar novos.
Para sobrescrever os arquivos, basta, quando executar o programa, digitar "2" quando for solicitado.



EXPLICAÇÕES GERAIS 
O trabalho contém, ao todo, 5 TADS: Histórico, Paciente, Lista de Pacientes, Triagem (Fila de espera) e IO. A dependência deles é a seguinte: 
Histórico - Não tem dependências 
Paciente - Extende o histórico 
Lista de pacientes - Extende o paciente (que extende o histórico) 
Triagem - Extende o paciente e a lista de pacientes 
IO - Extende a lista de pacientes e a triagem 

IMPLEMENTAÇÕES 
Para o paciente, foi apenas criado um struct com funções. Para o IO, apenas funções. 
Para o histórico, foi implementada uma PILHA estática. 
Para a lista de pacientes, foi implementada uma LISTA dinâmica ordenada encadeada com nó cabeça. 
Para a triagem, foi implementada uma FILA estática circular. 

ALOCAÇÕES DINÂMICAS 
Para estruturas pequenas, como os procedimentos (matriz de 10x100) e o vetor de ponteiros da triagem, foram usadas variáveis na Stack. Porém, todas as funções de CRIAR TADs utilizam alocações dinâmicas para alocarem os structs. As funções de consultas (da triagem e da lista de pacientes) também criam alocações dinâmicas para armazenarem os resultados. A liberação dessas 2 memórias fica a cargo do usuário. O código foi checado com valgrind e não obteve vazamentos de memória. 

FUNÇÕES EXTRAS 
Apesar de não especificadas no PDF, implementamos funções adicionais que auxiliariam na utilização do menu. Por exemplo, ordenamos por QuickSort a lista de pacientes antes de imprimir (por padrão, ela é ordenada por ID, mas o usuário pode ordenar por nome). ALém disso, para evitar redigitar comandos, o programa entra num while caso o usuário digite um nome/id de paciente ou prescrição com mais caracteres do que devia (esse loop é finalizável digitando '*'). O usuário também pode buscar pacientes por ID ou por NOME e também pode optar por criar um novo registro ou carregar o já existente no arquivo. 