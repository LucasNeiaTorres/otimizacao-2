#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "triangulo.h"
#include "parametros.h"

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

int eh_afinidade(int x, int y, int **afinidades, int num_afinidades)
{
    int i;
    for (i = 0; i < num_afinidades; i++)
    {
        // printf("%d == %d | %d == %d || %d == %d | %d == %d\n", x, afinidades[i][0], y, afinidades[i][1], y, afinidades[i][0], x, afinidades[i][1]);
        if ((x == afinidades[i][0] && y == afinidades[i][1]) || (y == afinidades[i][0] && x == afinidades[i][1]))
            return 1;
    }
    return 0;
}

int calcula_afinidades(int **afinidades, int *grupo, int tamanho, int num_afinidades)
{
    int i, j;
    int qtde = 0;
    for (i = 0; i < tamanho; i++)
    {
        for (j = i + 1; j < tamanho; j++)
        {
            if (eh_afinidade(grupo[i], grupo[j], afinidades, num_afinidades))
                qtde++;
        }
    }
    return qtde;
}

int calcula_conflitos(int **conflitos, int *grupo, int tamanho, int num_conflitos)
{
    int i, j;
    int qtde = 0;
    for (i = 0; i < tamanho; i++)
    {
        for (j = i + 1; j < tamanho; j++)
        {
            if (eh_conflito(grupo[i], grupo[j], conflitos, num_conflitos))
                qtde++;
        }
    }
    return qtde;
}

// pega primeiro elemento e o remove
int primeiro_elemento(int *vetor, int tamanho)
{
    int i;
    int elemento = 0;
    for (i = 0; i < tamanho; i++)
    {
        if (vetor[i] != 0)
        {
            elemento = vetor[i];
            vetor[i] = 0;
            break;
        }
    }
    return elemento;
}

void inclui_elemento(int *vetor, int elemento)
{
    int i = 0;
    while (vetor[i] != 0)
        i++;
    vetor[i] = elemento;
}

void atribuirVetor(int *vetorDestino, int *vetorOrigem, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
        vetorDestino[i] = vetorOrigem[i];
}

int eh_vazio(int *vetor, int tamanho)
{
    int i;
    for (i = 0; i < tamanho; i++)
    {
        if (vetor[i] != 0)
            return 0;
    }
    return 1;
}

void imprime(int *vetor, int tamanho)
{
    int i;
    for (i = 0; i < tamanho; i++)
        printf("%d ", vetor[i]);
    printf("\n");
}

void insere_elemento(int *copia_atribuicoes, int num_itens, int elemento)
{
    int i = 0;
    while (copia_atribuicoes[i] != 0)
        i++;
    copia_atribuicoes[i] = elemento;
}

int retorna_indice(int *atribuicoes, int elemento, int num_itens)
{
    int i;
    for (i = 0; i < num_itens; i++)
    {
        if (atribuicoes[i] == elemento)
            return i;
    }
    return 0;
}

int nao_atribuido(int *atribuicoes, int num_itens, int elemento)
{
    int i;
    for (i = 0; i < num_itens; i++)
    {
        if (atribuicoes[i] == elemento)
            return 1;
    }
    return 0;
}

int busca_afinidade(int **afinidades, int *atribuicoes, int num_afinidades, int *copia_atribuicoes, int num_itens, int elemento)
{
    int i;
    for (i = 0; i < num_afinidades; i++)
    {
        // printf("ELemento %d \\ ( %d %d )\n",elemento,afinidades[i][0], afinidades[i][1]);
        if ((elemento == (afinidades[i][0])) && (nao_atribuido(atribuicoes, num_itens, afinidades[i][1]) == 1))
        {
            insere_elemento(copia_atribuicoes, num_itens, afinidades[i][1]);
            atribuicoes[(retorna_indice(atribuicoes, afinidades[i][1], num_itens))] = 0;
            busca_afinidade(afinidades, atribuicoes, num_afinidades, copia_atribuicoes, num_itens, afinidades[i][1]);
        }
        else if ((elemento == (afinidades[i][1])) && (nao_atribuido(atribuicoes, num_itens, afinidades[i][0]) == 1))
        {
            insere_elemento(copia_atribuicoes, num_itens, afinidades[i][0]);
            atribuicoes[(retorna_indice(atribuicoes, afinidades[i][0], num_itens))] = 0;
            busca_afinidade(afinidades, atribuicoes, num_afinidades, copia_atribuicoes, num_itens, afinidades[i][0]);
        }
    }
}

void atribui_afinidade(int *copia_atribuicoes, int *atribuicoes, int num_itens, int **afinidades, int num_afinidades)
{
    int i;
    int elemento = 0;
    for (i = 0; i < num_itens; i++)
    {
        if (atribuicoes[i] != 0)
        {
            elemento = atribuicoes[i];
            break;
        }
    }
    insere_elemento(copia_atribuicoes, num_itens, elemento);
    atribuicoes[retorna_indice(atribuicoes, elemento, num_itens)] = 0;
    busca_afinidade(afinidades, atribuicoes, num_afinidades, copia_atribuicoes, num_itens, elemento);
}

int retorna_conflitos(int **conflitos, int num_conflitos, int elemento)
{
    int i;
    int qnt = 0;
    for (i = 0; i < num_conflitos; i++)
    {
        // printf("elemento:%d \n",elemento);
        if (((conflitos[i][0]) == elemento) || ((conflitos[i][1]) == elemento))
            qnt++;
    }
    return qnt;
}

int valor_maximo(int *vetorA, int *vetorB, int num_itens, int **conflitos, int num_conflitos)
{
    int i;
    int maior = 0;
    int conflitosA = 0;
    int conflitosB = 0;
    // printf("Vetor: ");
    for (i = 0; i < num_itens; i++)
    {
        // printf("%d .",vetorB[i]);/
        if (vetorA[i] != 0)
            conflitosA = (retorna_conflitos(conflitos, num_conflitos, vetorA[i]));
        if (vetorB[i] != 0)
            conflitosB = (retorna_conflitos(conflitos, num_conflitos, vetorB[i]));
        if (conflitosA > maior)
            maior = conflitosA;
        if (conflitosB > maior)
            maior = conflitosB;
    }
    // printf("Maior conflito: %d\n", maior);
    // printf("\n");
    return maior;
}



void branchBound(Node *node, int **conflitos, int **afinidades, int *atribuicoes, int num_itens, int num_conflitos, int num_afinidades, Node *melhor_solucao, parametros_t parametros)
{
    printf("Grupo A: ");
    imprime(node->grupoA, num_itens);
    printf("Grupo B: ");
    imprime(node->grupoB, num_itens);
    printf("O que falta: ");
    imprime(atribuicoes, num_itens);
    printf("Conflitos: %d\n", node->conflitos);
    printf("Afinidades: %d\n", node->afinidades);
    printf("Melhor solucao até então: %d\n", melhor_solucao->conflitos);
    printf("\n QUANTIDADE TRIANGULO %d\n", escolhe_heroi(conflitos, num_conflitos, atribuicoes, num_itens));
    printf("-------------------------\n");
    int maior_valor = 0;
    maior_valor = valor_maximo(node->grupoA, node->grupoB, num_itens, conflitos, num_conflitos);
    printf("MAIOR VALOR ENCONTRADO DENTRE INSERIDOS: %d\n", maior_valor);
    // caso base
    if (eh_vazio(atribuicoes, num_itens) == 1)
    {
        if ((node->conflitos <= melhor_solucao->conflitos) && (node->afinidades == num_afinidades))
            *melhor_solucao = *node;
        return;
    }

    int *atribuicoesAux = (int *)calloc(num_itens, sizeof(int));
    atribuirVetor(atribuicoesAux, atribuicoes, num_itens);

    int *vetorAuxiliarA = (int *)calloc(num_itens, sizeof(int));
    int *vetorAuxiliarB = (int *)calloc(num_itens, sizeof(int));

    atribuirVetor(vetorAuxiliarA, node->grupoA, num_itens);
    atribuirVetor(vetorAuxiliarB, node->grupoB, num_itens);

    int proximo_elemento;
    // printf("%d\n", parametros.viabilidade);
    if (parametros.viabilidade == 1)
    {
        atribui_afinidade(vetorAuxiliarA, atribuicoesAux, num_itens, afinidades, num_afinidades);
        atribuirVetor(atribuicoesAux, atribuicoes, num_itens);
        atribui_afinidade(vetorAuxiliarB, atribuicoesAux, num_itens, afinidades, num_afinidades);
    }
    else
    {
        proximo_elemento = primeiro_elemento(atribuicoesAux, num_itens);
        inclui_elemento(vetorAuxiliarA, proximo_elemento);
        inclui_elemento(vetorAuxiliarB, proximo_elemento);
    }

    if (parametros.professor == 1)
    {
        int funcao_limitante = node->conflitos + escolhe_heroi(conflitos, num_conflitos, atribuicoesAux, num_itens) + maior_valor;
        if (funcao_limitante >= melhor_solucao->conflitos)
            return;
    }

    if ((parametros.otimalidade == 1) && (node->conflitos >= melhor_solucao->conflitos))
    {
        return;
    }
    else
    {
        int conflitos_atual = calcula_conflitos(conflitos, vetorAuxiliarA, num_itens, num_conflitos);
        conflitos_atual = conflitos_atual + calcula_conflitos(conflitos, node->grupoB, num_itens, num_conflitos);
        int afinidades_atual = calcula_afinidades(afinidades, vetorAuxiliarA, num_itens, num_afinidades);
        afinidades_atual = afinidades_atual + calcula_afinidades(afinidades, node->grupoB, num_itens, num_afinidades);
        Node *nodo_esquerda = cria_nodo(conflitos_atual, afinidades_atual, vetorAuxiliarA, node->grupoB, num_itens);
        node->esquerda = nodo_esquerda;
        branchBound(nodo_esquerda, conflitos, afinidades, atribuicoesAux, num_itens, num_conflitos, num_afinidades, melhor_solucao, parametros);

        // atribuirVetor(atribuicoesAux, atribuicoes, num_itens);
        // atribui_afinidade(vetorAuxiliarB, atribuicoesAux, num_itens, afinidades, num_afinidades, proximo_elemento);
        conflitos_atual = calcula_conflitos(conflitos, vetorAuxiliarB, num_itens, num_conflitos);
        conflitos_atual = conflitos_atual + calcula_conflitos(conflitos, node->grupoA, num_itens, num_conflitos);
        afinidades_atual = calcula_afinidades(afinidades, vetorAuxiliarB, num_itens, num_afinidades);
        afinidades_atual = afinidades_atual + calcula_afinidades(afinidades, node->grupoA, num_itens, num_afinidades);
        Node *nodo_direita = cria_nodo(conflitos_atual, afinidades_atual, node->grupoA, vetorAuxiliarB, num_itens);
        node->direita = nodo_direita;
        branchBound(nodo_direita, conflitos, afinidades, atribuicoesAux, num_itens, num_conflitos, num_afinidades, melhor_solucao, parametros);
    }

    free(atribuicoesAux);
    free(vetorAuxiliarA);
    free(vetorAuxiliarB);
    return;
}

int main(int argc, char *argv[])
{
    int num_itens;      // n
    int num_conflitos;  // m
    int num_afinidades; // k
    int **conflitos;
    int **afinidades;
    int *grupoA;
    int *grupoB;
    int *atribuicoes;
    int arg;
    parametros_t parametros;

    parametros.otimalidade = 1;
    parametros.viabilidade = 1;
    parametros.professor = 0;

    for (arg = 0; arg < argc; arg++)
    {
        if (!strcmp(argv[arg], "-o"))
            parametros.otimalidade = 0;
        else if (!strcmp(argv[arg], "-f"))
            parametros.viabilidade = 0;
        else if (!strcmp(argv[arg], "-a"))
            parametros.professor = 1;
    }
    printf("-o: %d  -f: %d  -a: %d\n", parametros.otimalidade, parametros.viabilidade, parametros.professor);
    // Leitura dos dados
    scanf("%d %d %d", &num_itens, &num_conflitos, &num_afinidades);

    // cria matriz de conflitos
    int i;
    conflitos = (int **)calloc(num_conflitos, sizeof(int *));
    for (i = 0; i < num_conflitos; i++)
    {
        conflitos[i] = (int *)calloc(2, sizeof(int));
        scanf("%d %d", &conflitos[i][0], &conflitos[i][1]);
    }

    // cria matriz de afinidades
    afinidades = (int **)calloc(num_afinidades, sizeof(int *));
    for (i = 0; i < num_afinidades; i++)
    {
        afinidades[i] = (int *)calloc(2, sizeof(int));
        scanf("%d %d", &afinidades[i][0], &afinidades[i][1]);
    }
    // cria vetores dos grupos divididos pelo algoritmo
    grupoA = (int *)calloc(num_itens, sizeof(int));
    grupoB = (int *)calloc(num_itens, sizeof(int));

    // cria vetor de atribuicoes
    atribuicoes = (int *)calloc(num_itens, sizeof(int));
    for (i = 0; i < num_itens; i++)
    {
        atribuicoes[i] = i + 1;
    }

    Node *melhor_solucao = cria_nodo(num_conflitos, 0, grupoA, grupoB, num_itens);
    Node *raiz = cria_nodo(num_itens, 0, grupoA, grupoB, num_itens);

    branchBound(raiz, conflitos, afinidades, atribuicoes, num_itens, num_conflitos, num_afinidades, melhor_solucao, parametros);
    printf("Melhor solucao: %d\n", melhor_solucao->conflitos);
    imprime(melhor_solucao->grupoA, num_itens);
    imprime(melhor_solucao->grupoB, num_itens);

    printf("Nós totais: %d\n", conta_nos(raiz));

    free_tree(raiz);
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