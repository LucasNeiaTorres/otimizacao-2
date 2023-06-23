#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int num_itens; // n
    int num_conflitos; // m
    int num_afinidades; // k
    int **conflitos;
    int **afinidades;
    int *grupoA;
    int *grupoB;

    // Leitura dos dados
    scanf("%d %d %d", &num_itens, &num_conflitos, &num_afinidades);

    // cria matriz de conflitos
    int i;
    conflitos = (int **)calloc(num_conflitos, sizeof(int *));
    for (i = 0; i < num_conflitos; i++) {
        conflitos[i] = (int *)calloc(2, sizeof(int));
        scanf("%d %d", &conflitos[i][0], &conflitos[i][1]);
    }

    // cria matriz de afinidades
    afinidades = (int **)calloc(num_afinidades, sizeof(int *));
    for (i = 0; i < num_afinidades; i++) {
        afinidades[i] = (int *)calloc(2, sizeof(int));
        scanf("%d %d", &afinidades[i][0], &afinidades[i][1]);
    }

    // cria vetores dos grupos divididos pelo algoritmo
    grupoA = (int *)calloc(num_itens, sizeof(int));
    grupoB = (int *)calloc(num_itens, sizeof(int));

    // TODO: implementar funcao objetivo
    // min (sum (sum (conflitos[i][j] * (grupoA[i] - grupoB[j]))))
    // min conflitos(grupoA) + conflitos(grupoB)
    // max (sum (sum (afinidades[i][j] * (grupoA[i] - grupoB[j]))))
    // max afinidades(grupoA) + afinidades(grupoB)

    for (i = 0; i < num_conflitos; i++)
        free(conflitos[i]);
    free(conflitos);
    for (i = 0; i < num_afinidades; i++)
        free(afinidades[i]);
    free(afinidades);
    free(grupoA);
    free(grupoB);
    return 0;
}