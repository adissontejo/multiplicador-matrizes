.PHONY: all
all: bin/gerador bin/formatador bin/processos bin/sequencial

bin/gerador: bin src/gerador.c
	gcc -o bin/gerador src/gerador.c

bin/formatador: bin src/formatador.c
	gcc -o bin/formatador src/formatador.c

bin/processos: bin src/processos.c
	gcc -o bin/processos src/processos.c -lm

bin/sequencial: bin src/sequencial.c
	gcc -o bin/sequencial src/sequencial.c -lm

bin:
	mkdir bin

.PHONY: clean
clean: bin_clean in_clean out_clean

.PHONY: bin_clean
bin_clean:
	rm -rf bin

.PHONY: in_clean
in_clean:
	rm -rf input/*.txt

.PHONY: out_clean
out_clean:
	find ./output -type f -name "*.txt" -delete
