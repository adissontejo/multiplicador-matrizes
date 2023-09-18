#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <syscall.h>
#include <sys/time.h>
#include <sys/types.h>
#include <pthread.h>

int n1, m1, n2, m2; // n1,n2 -> numero de linhas | m1,m2 -> numero de colunas
int p; // -> numero de elementos por theard
struct timeval tempo_ini;
pid_t pid;

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

void * calcula_elementos(void * tid) {
    printf("tid: %d", (int)(size_t) tid);
    int ini = p * ((int)(size_t) tid);
    int fim = p * ((int)(size_t) tid + 1);

    if (fim > n1 * m2) {
        fim = n1 * m2;
    }

    int* matriz1 = le_matriz(&n1, &m1, "./input/A.txt");
    int* matriz2 = le_matriz(&n2, &m2, "./input/B.txt");

    char caminho_arquivo[255];

    sprintf(caminho_arquivo, "./output/threads/saida_%d.txt", (int)(size_t) tid);

    FILE* arquivo = fopen(caminho_arquivo, "w");

    fprintf(arquivo, "%d %d %d\n", n1, m2, fim - ini);

    for (int i = ini; i < fim; i++) {
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

    struct timeval tempo_fim, diff;

    gettimeofday(&tempo_fim, NULL);

    timersub(&tempo_fim, &tempo_ini, &diff);

    fprintf(arquivo, "\n%ld.%06ld segundos\n", diff.tv_sec, diff.tv_usec);

    fclose(arquivo);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <numero_de_elementos_por_processo>\n", argv[0]);

        exit(0);
    }

    p = atoi(argv[1]);

    if (m1 != n2) {
        printf("Matrizes incompatíveis\n");
        exit(0);
    }

    int total_threads = ceil((double) n1 * m2 / p);

    pthread_t threads[total_threads];
    int i, status;
    void* thread_retorno;

    gettimeofday(&tempo_ini, NULL);

    pid = fork();
    for (i = 0; i < total_threads; i++) {
        status = pthread_create(&threads[i], NULL, calcula_elementos, (void*)(size_t) i);

        if(status != 0) return (1);
    }

    for (i = 0; i < total_threads; i++) {
        retorno = pthread_join(threads[i], &thread_retorno);
    }

    return 0;
}