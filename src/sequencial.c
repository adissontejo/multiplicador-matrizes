#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int n1, m1, n2, m2; // n1,n2 -> numero de linhas | m1,m2 -> numero de colunas
int* matriz1, * matriz2;
struct timeval tempo_ini;

int acessa_matriz(int* matriz, int i, int j, int n, int m) {
    // i, j -> posicoes de uma matriz lin e col | n,m numero de linhas e colunas da matriz
    int el = i * m + j;

    return matriz[el];
}

int * le_matriz(int* n, int* m, char* caminho_arquivo) {
    FILE* arquivo = fopen(caminho_arquivo, "r");

    fscanf(arquivo, "%d %d", n, m);

    int* matriz = malloc(sizeof(int)*(*n)*(*m));

    int pos = 0;

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            fscanf(arquivo, "%d", &matriz[pos]);
            pos++;
        }
    }

    fclose(arquivo);

    return matriz;
}

void calcula_elementos() {
    char caminho_arquivo[255];

    sprintf(caminho_arquivo, "./output/sequencial/saida.txt");

    FILE* arquivo = fopen(caminho_arquivo, "w");

    fprintf(arquivo, "%d %d\n", n1, m2);

    for (int i = 0; i < (n1*m2); i++) {
        int linha = i / m2;
        int coluna = i % m2;

        int soma = 0;

        for (int j = 0; j < m1; j++) {
            int a = acessa_matriz(matriz1, linha, j, n1, m1);
            int b = acessa_matriz(matriz2, j, coluna, n2, m2);

            soma += a * b;
        }

        fprintf(arquivo, "%d.%d %d\n", (linha + 1), (coluna + 1), soma);
    }

    free(matriz1);
    free(matriz2);

    struct timeval tempo_fim, diff;

    gettimeofday(&tempo_fim, NULL);

    timersub(&tempo_fim, &tempo_ini, &diff);

    fprintf(arquivo, "\n%ld.%06ld segundos\n", diff.tv_sec, diff.tv_usec);

    fclose(arquivo);
}

int main(int argc, char *argv[]) {
    matriz1 = le_matriz(&n1, &m1, "./input/A.txt");
    matriz2 = le_matriz(&n2, &m2, "./input/B.txt");

    if (m1 != n2) {
        printf("Matrizes incompatíveis\n");
    }else{
        gettimeofday(&tempo_ini, NULL);
        calcula_elementos();
    }

    return 0;
}

