#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <syscall.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>

int n1, m1, n2, m2; // n1,n2 -> numero de linhas | m1,m2 -> numero de colunas
int p; // -> numero de elementos por processo
int segmento1, segmento2; // -> segmentos das memorias compartilhadas
struct timeval tempo_ini;

int acessa_matriz(int* matriz, int i, int j, int n, int m) {
    // i, j -> posicoes de uma matriz lin e col | n,m numero de linhas e colunas da matriz
    int el = i * m + j;

    return matriz[el];
}

int le_matriz(int* n, int* m, char* caminho_arquivo) {
    FILE* arquivo = fopen(caminho_arquivo, "r");

    fscanf(arquivo, "%d %d", n, m);

    int segmento = shmget(IPC_PRIVATE, sizeof(int) * (*n) * (*m), IPC_CREAT | 0666);

    int* matriz = shmat(segmento, NULL, 0);

    int pos = 0;

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            fscanf(arquivo, "%d", &matriz[pos]);

            pos++;
        }
    }

    shmdt(matriz);

    fclose(arquivo);

    return segmento;
}

void limpa_matriz(int segmento) {
    shmctl(segmento, IPC_RMID, NULL);
}

void calcula_elementos(int id_processo) {
    int ini = p * id_processo;
    int fim = p * (id_processo + 1);

    if (fim > n1 * m2) {
        fim = n1 * m2;
    }

    int* matriz1 = shmat(segmento1, NULL, 0);
    int* matriz2 = shmat(segmento2, NULL, 0);

    char caminho_arquivo[255];

    sprintf(caminho_arquivo, "./output/processos/saida_%d.txt", id_processo);

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

    shmdt(matriz1);
    shmdt(matriz2);

    struct timeval tempo_fim, diff;

    gettimeofday(&tempo_fim, NULL);

    timersub(&tempo_fim, &tempo_ini, &diff);

    fprintf(arquivo, "%ld.%06ld segundos\n", diff.tv_sec, diff.tv_usec);

    fclose(arquivo);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <numero_de_elementos_por_processo>\n", argv[0]);

        exit(0);
    }

    p = atoi(argv[1]);

    segmento1 = le_matriz(&n1, &m1, "./input/A.txt");
    segmento2 = le_matriz(&n2, &m2, "./input/B.txt");

    if (m1 != n2) {
        printf("Matrizes incompatíveis\n");

        limpa_matriz(segmento1);
        limpa_matriz(segmento2);

        exit(0);
    }

    int total_processos = ceil((double) n1 * m2 / p);

    int id = -1, pid[total_processos];

    gettimeofday(&tempo_ini, NULL);

    for (int i = 0; i < total_processos; i++) {
        pid[i] = fork();

        if (pid[i] == 0) {
            id = i;

            break;
        }
        // fazer else if < 0 - erros
    }

    if (id != -1) {
        calcula_elementos(id);

        exit(0);
    }

    for (int i = 0; i < total_processos; i++) {
        waitpid(pid[i], NULL, 0);
    }

    return 0;
}
