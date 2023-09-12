bin/gerador: bin src/gerador.c
	gcc -o bin/gerador src/gerador.c

bin:
	mkdir bin

