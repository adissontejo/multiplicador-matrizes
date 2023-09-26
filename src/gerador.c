#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gera_matriz(int n, int m, char* caminho_arquivo) {
    FILE* arquivo = fopen(caminho_arquivo, "w");

    fprintf(arquivo, "%d %d\n", n, m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j ++) {
            if (j) {
                fprintf(arquivo, " ");
            }

            fprintf(arquivo, "%d", rand() % 100);
        }

        fprintf(arquivo, "\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 5 && argc != 6) {
        printf("Uso: %s <numero_de_linhas_A> <numero_de_colunas_A> <numero_de_linhas_B> <numero_de_colunas_B> [randomizador_opcional]\n", argv[0]);

        return 0;
    }

    int n1 = atoi(argv[1]);
    int m1 = atoi(argv[2]);
    int n2 = atoi(argv[3]);
    int m2 = atoi(argv[4]);

    if (argc == 6) {
        srand(time(NULL) + atoi(argv[5]));
    } else {
        srand(time(NULL));
    }

    gera_matriz(n1, m1, "./input/A.txt");
    gera_matriz(n2, m2, "./input/B.txt");

    return 0;
}
