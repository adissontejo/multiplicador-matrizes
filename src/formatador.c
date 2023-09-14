#include <stdio.h>

void formata(char* caminho_pasta) {
    char caminho_arquivo_leitura[255], caminho_arquivo_escrita[255];

    sprintf(caminho_arquivo_leitura, "%s/saida_0.txt", caminho_pasta);
    sprintf(caminho_arquivo_escrita, "%s/saida.txt", caminho_pasta);

    FILE* arquivo_leitura = fopen(caminho_arquivo_leitura, "r");
    FILE* arquivo_escrita = fopen(caminho_arquivo_escrita, "w");

    int n, m, p, cont = 0;
    double maior_tempo = 0;

    fscanf(arquivo_leitura, "%d %d %d", &n, &m, &p);

    fprintf(arquivo_escrita, "%d %d\n", n, m);

    int matriz[n * m];

    while (cont < n * m) {
        if (cont != 0) {
            sprintf(caminho_arquivo_leitura, "%s/saida_%d.txt", caminho_pasta, cont / p);

            arquivo_leitura = fopen(caminho_arquivo_leitura, "r");

            fscanf(arquivo_leitura, "%d %d %d", &n, &m, &p);
        }

        for (int i = 0; i < p; i++) {
            fscanf(arquivo_leitura, "%d", &matriz[cont]);

            cont++;
        }

        double tempo;

        fscanf(arquivo_leitura, "%lf", &tempo);

        if (tempo > maior_tempo) {
            maior_tempo = tempo;
        }

        fclose(arquivo_leitura);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            if (j) {
                fprintf(arquivo_escrita, " ");
            }

            fprintf(arquivo_escrita, "%d", matriz[i * m + j]);
        }

        fprintf(arquivo_escrita, "\n");
    }

    fprintf(arquivo_escrita, "%lf segundos\n", maior_tempo);

    fclose(arquivo_escrita);
}

int main() {
    formata("./output/processos");
    formata("./output/threads");

    return 0;
}
