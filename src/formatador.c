#include <stdio.h>
#include <string.h>

void formata(char* caminho_pasta) {
    char caminho_arquivo_leitura[255], caminho_arquivo_escrita[255], temp[50];

    sprintf(caminho_arquivo_leitura, "%s/saida_0.txt", caminho_pasta);
    sprintf(caminho_arquivo_escrita, "%s/saida.txt", caminho_pasta);

    FILE* arquivo_leitura = fopen(caminho_arquivo_leitura, "r");
    FILE* arquivo_escrita = fopen(caminho_arquivo_escrita, "w");

    int n, m, p, cont = 0;
    double maior_tempo = 0;

    fscanf(arquivo_leitura, "%d %d %d", &n, &m, &p);

    fprintf(arquivo_escrita, "%d %d\n", n, m);

    while (cont < n * m) {
        if (cont != 0) {
            sprintf(caminho_arquivo_leitura, "%s/saida_%d.txt", caminho_pasta, cont / p);

            arquivo_leitura = fopen(caminho_arquivo_leitura, "r");

            fscanf(arquivo_leitura, "%d %d %d", &n, &m, &p);
        }

        for (int i = 0; i < p; i++) {
            int el;

            fscanf(arquivo_leitura, "%s %d", temp, &el);

            fprintf(arquivo_escrita, "%s %d\n", temp, el);

            cont++;
        }

        double tempo;

        fscanf(arquivo_leitura, "%lf", &tempo);

        if (tempo > maior_tempo) {
            maior_tempo = tempo;
        }

        fclose(arquivo_leitura);
    }

    fprintf(arquivo_escrita, "%lf segundos\n", maior_tempo);

    fclose(arquivo_escrita);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Uso: %s <processos | threads>\n", argv[0]);

        return 0;
    }

    if (strcmp(argv[1], "processos") == 0) {
        formata("./output/processos");
    } else if (strcmp(argv[1], "threads") == 0) {
        formata("./output/threads");
    } else {
        printf("Argumento inválido.\n");
    }

    return 0;
}
