parametrosCompilacao=-Wall -std=c99
arquivos=arvore.o separacaoGrupos.o triangulo.o
all: separa

separa: ${arquivos}
	gcc -o separa ${arquivos} $(parametrosCompilacao)

.o: .c
	gcc -c *.c $(parametrosCompilacao)

run: separa
	./separa < entrada.txt > saida.txt
	lp_solve saida.txt

clean:
	rm -f *.o *.gch separa 

purge: clean
	-rm -f separa