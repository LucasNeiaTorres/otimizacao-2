parametrosCompilacao=-Wall -std=c99
all: separa

separa: separacaoGrupos.o
	gcc -o separa separacaoGrupos.o $(parametrosCompilacao)

.o: .c
	gcc -c *.c $(parametrosCompilacao)

run: separa
	./separa < entrada.txt > saida.txt
	lp_solve saida.txt

clean:
	rm -f *.o *.gch separa 

purge: clean
	-rm -f separa