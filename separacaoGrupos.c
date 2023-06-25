#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

// TODO: implementar funcao objetivo
// min conflitos(grupoA) + conflitos(grupoB)
// s.a len(grupoA) + len(grupoB) = n
// s.a len(grupoA) > 0
// s.a len(grupoB) > 0
// s.a afinidades c grupoA

// Função para calcular o limite superior (upper bound) de um nó da árvore de busca
// int calculateUpperBound(int** conflicts, int** affinities, int* assignment, int numItems, int numConflicts, int numAffinities) {
//     int conflictsCount = calculateConflicts(conflicts, assignment, numItems, numConflicts);
//     int affinitiesCount = 0;
//     for (int i = 0; i < numAffinities; i++) {
//         int item1 = affinities[i][0];
//         int item2 = affinities[i][1];
//         if (assignment[item1] == assignment[item2]) {
//             affinitiesCount++;
//         }
//     }
//     return conflictsCount + affinitiesCount;
// }

int eh_conflito(int x, int y, int **conflitos, int num_conflitos) {
    int i;
    for(i = 0; i < num_conflitos; i++) {
        // printf("%d == %d | %d == %d || %d == %d | %d == %d\n", x, conflitos[i][0], y, conflitos[i][1], y, conflitos[i][0], x, conflitos[i][1]);
        if((x == conflitos[i][0] && y == conflitos[i][1]) || (y == conflitos[i][0] && x == conflitos[i][1]))
            return 1;
    }
    return 0;
}

int calcula_conflitos(int **conflitos, int *grupo, int tamanho, int num_conflitos) {
    int i, j;
    int qtde = 0;
    for(i = 0; i < tamanho; i++) {
        for(j = i+1; j < tamanho; j++) {
            if(eh_conflito(grupo[i], grupo[j], conflitos, num_conflitos))
                qtde++;
        }
    }
    return qtde;
}

// pega primeiro elemento e o remove
int primeiro_elemento(int *vetor, int tamanho) {
    int i;
    int elemento = 0;
    for(i = 0; i < tamanho; i++) {
        if(vetor[i] != 0) {
            elemento = vetor[i];
            vetor[i] = 0;
            break;
        }
    }
    return elemento;
}

void inclui_elemento(int *vetor, int elemento) {
    int i = 0;
    while(vetor[i] != 0) 
        i++;
    vetor[i] = elemento;
}

void atribuirVetor(int *vetorDestino, int *vetorOrigem, int tamanho) {
    for (int i = 0; i < tamanho; i++)
        vetorDestino[i] = vetorOrigem[i];
}

int eh_vazio(int *vetor, int tamanho) {
    int i;
    for(i = 0; i < tamanho; i++) {
        if(vetor[i] != 0)
            return 0;
    }
    return 1;
}

void imprime(int *vetor, int tamanho) {
    int i;
    for(i = 0; i < tamanho; i++)
        printf("%d ", vetor[i]);
    printf("\n");
}

void branchBound(Node *node, int **conflitos, int **afinidades, int *atribuicoes, int num_itens, int num_conflitos, int num_afinidades, Node *melhor_solucao) {
    printf("Grupo A: ");
    imprime(node->grupoA, num_itens);
    printf("Grupo B: ");
    imprime(node->grupoB, num_itens);
    printf("O que falta: ");
    imprime(atribuicoes, num_itens);
    printf("Conflitos: %d\n", node->conflitos);
    printf("Melhor solucao até então: %d\n", melhor_solucao->conflitos);
    printf("-------------------------\n");
    // caso base
    if(eh_vazio(atribuicoes, num_itens) == 1) {
        if (node->conflitos < melhor_solucao->conflitos) // e todas as afinidades
            *melhor_solucao = *node; 
        return;
    }
    int *atribuicoesAux = (int *)calloc(num_itens, sizeof(int));
    atribuirVetor(atribuicoesAux, atribuicoes, num_itens);

    int proximo_elemento = primeiro_elemento(atribuicoesAux, num_itens);
    int *vetorAuxiliarA = (int *)calloc(num_itens, sizeof(int));
    int *vetorAuxiliarB = (int *)calloc(num_itens, sizeof(int));

    atribuirVetor(vetorAuxiliarA, node->grupoA, num_itens);
    atribuirVetor(vetorAuxiliarB, node->grupoB, num_itens);

    inclui_elemento(vetorAuxiliarA, proximo_elemento);
    int conflitos_atual = calcula_conflitos(conflitos, vetorAuxiliarA, num_itens, num_conflitos);
    conflitos_atual = conflitos_atual + calcula_conflitos(conflitos, node->grupoB, num_itens, num_conflitos);
    Node *nodo_esquerda = cria_nodo(conflitos_atual, vetorAuxiliarA, node->grupoB, num_itens);
    node->esquerda = nodo_esquerda;
    branchBound(nodo_esquerda, conflitos, afinidades, atribuicoesAux, num_itens, num_conflitos, num_afinidades, melhor_solucao);

    inclui_elemento(vetorAuxiliarB, proximo_elemento);
    conflitos_atual = calcula_conflitos(conflitos, vetorAuxiliarB, num_itens, num_conflitos);
    conflitos_atual = conflitos_atual + calcula_conflitos(conflitos, node->grupoA, num_itens, num_conflitos);
    Node *nodo_direita = cria_nodo(conflitos_atual, node->grupoA, vetorAuxiliarB, num_itens);
    node->direita = nodo_direita;
    branchBound(nodo_direita, conflitos, afinidades, atribuicoesAux, num_itens, num_conflitos, num_afinidades, melhor_solucao);
    
    free(atribuicoesAux);
    free(vetorAuxiliarA);
    free(vetorAuxiliarB);
    return;
}

int main() {
    int num_itens; // n
    int num_conflitos; // m
    int num_afinidades; // k
    int **conflitos;
    int **afinidades;
    int *grupoA;
    int *grupoB;
    int *atribuicoes;

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
    
    // cria vetor de atribuicoes
    atribuicoes = (int *)calloc(num_itens, sizeof(int));
    for (i = 0; i < num_itens; i++) {
        atribuicoes[i] = i+1;
    }

    Node *raiz = cria_nodo(num_itens, grupoA, grupoB, num_itens);
    Node *melhor_solucao = cria_nodo(num_itens, grupoA, grupoB, num_itens);

    branchBound(raiz, conflitos, afinidades, atribuicoes, num_itens, num_conflitos, num_afinidades, melhor_solucao);
    printf("Melhor solucao: %d\n", melhor_solucao->conflitos);
    imprime(melhor_solucao->grupoA, num_itens);
    imprime(melhor_solucao->grupoB, num_itens);

    exibe_arvore(raiz);
    // da free arvore
    // free_tree(raiz);
    free(melhor_solucao);
    free(atribuicoes);
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