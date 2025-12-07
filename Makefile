all: historico.o paciente.o listapaciente.o triagem.o io.o main.o
	@gcc TADhistorico.o TADpaciente.o TADlistapaciente.o TADtriagem.o TADio.o main.o -o main
	@echo "Programa compilado!"
historico.o:
	@gcc -c TADhistorico.c
paciente.o:
	@gcc -c TADpaciente.c
listapaciente.o:
	@gcc -c TADlistapaciente.c
triagem.o:
	@gcc -c TADtriagem.c
io.o:
	@gcc -c TADio.c
main.o:
	@gcc -c main.c
clean:
	@rm -f *.o main
	@echo "Arquivos apagados!"
reset: clean all
run:
	@echo "Executando o programa...\n"
	@./main
reboot: reset run