#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <syscall.h>
#include <sys/types.h>
#include <sys/wait.h>

int** le_matriz(int* n, int* m, char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");

    fscanf(arquivo, "%d %d", n, m);

    int** matriz = (int**) malloc(sizeof(int*) * *n);

    for (int i = 0; i < *n; i++) {
        matriz[i] = (int*) malloc(sizeof(int) * *m);

        for (int j = 0; j < *m; j ++) {
            fscanf(arquivo, "%d", &matriz[i][j]);
        }
    }

    fclose(arquivo);
}

void limpa_matriz(int** matriz, int n) {
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }

    free(matriz);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <numero_de_elementos_por_processo>\n", argv[0]);

        return 0;
    }

    int p = atoi(argv[1]);

    int n1, m1, n2, m2;

    int **ma = le_matriz(&n1, &m1, "./in/A.txt");
    int **mb = le_matriz(&n2, &m2, "./in/B.txt");

    if (m1 != n2) {
        printf("Matrizes incompatíveis\n");

        limpa_matriz(ma, n1);
        limpa_matriz(mb, n2);

        return 0;
    }

    int totalProcessos = ceil((double) n1 * m2 / p);

    int id = -1, pid[totalProcessos];

    for (int i = 0; i < totalProcessos; i++) {
        pid[i] = fork();

        if (pid[i] == 0) {
            id = i;

            break;
        }
    }

    if (id == -1) {
        for (int i = 0; i < totalProcessos; i++) {
            waitpid(pid[i], NULL, 0);
        }
    } else {
        int ini = id * p;
        int fim = (id + 1) * p;

        if (fim > n1 * m2) {
            fim = n1 * m2;
        }

        int linha_ini = ini / m2;
        int linha_fim = fim / m2;
        int coluna_ini = ini % m2;
        int coluna_fim = fim % m2;

        printf("Processo [%d]: de %d x %d até %d x %d\n", id, linha_ini, coluna_ini, linha_fim, coluna_fim);
    }
}
