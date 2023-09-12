.PHONY: all
all: bin/gerador bin/processos

bin/gerador: bin src/gerador.c
	gcc -o bin/gerador src/gerador.c

bin/processos: bin src/processos.c
	gcc -o bin/processos src/processos.c -lm

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
	rm -rf output/**/*.txt
