#include "triangulo.h"
#include <stdlib.h>
#include <stdio.h>

int eh_conflito(int x, int y, int **conflitos, int num_conflitos)
{
    int i;
    for (i = 0; i < num_conflitos; i++)
    {
        // printf("%d == %d | %d == %d || %d == %d | %d == %d\n", x, conflitos[i][0], y, conflitos[i][1], y, conflitos[i][0], x, conflitos[i][1]);
        if ((x == conflitos[i][0] && y == conflitos[i][1]) || (y == conflitos[i][0] && x == conflitos[i][1]))
            return 1;
    }
    return 0;
}

int atribuido(int *atribuicoes, int num_items, int super_heroi)
{
    if (atribuicoes[(super_heroi - 1)] == super_heroi)
        return 1;
    int i;
    for (i = 0; i < num_items; i++)
    {
        if (super_heroi == atribuicoes[i])
            return 1;
    }
    return 0;
}

int ultima_posicao(Triangulo *triangulos, int num_items)
{
    int i;
    for (i = 0; i < num_items; i++)
    {
        if (triangulos[i].x == 0 && triangulos[i].y == 0 && triangulos[i].z == 0)
            return i;
    }
    return 0;
}

int existe_par(Triangulo *triangulos, int num_items, int x, int y)
{
    int i = 0;
    int indiceAtual = ultima_posicao(triangulos, num_items);
    printf("\n%d %d == ",x, y);
    for (i = 0; i < indiceAtual; i++)
    {
        printf("%d %d %d\n", triangulos[i].x, triangulos[i].y, triangulos[i].z);
        if ((x == triangulos[i].x && y == triangulos[i].y) || (x == triangulos[i].y && y == triangulos[i].x)) {
            printf("deu iguallllllllllll\n");
            return 1;
        }
        else if ((x == triangulos[i].x && y == triangulos[i].z) || (x == triangulos[i].z && y == triangulos[i].x))
            return 1;
        else if ((x == triangulos[i].y && y == triangulos[i].z) || (x == triangulos[i].z && y == triangulos[i].y))
            return 1;
    }
    return 0;
}

int eh_triangulo(int heroi_inicial, int heroi_conflito, int **conflitos, int num_conflitos, int *atribuicoes, int num_items, int posicao, Triangulo *triangulos)
{
    int i;
    int indiceAtual = ultima_posicao(triangulos, num_items);
    for (i = posicao + 1; i < num_conflitos; i++)
    {
        if ((heroi_conflito == conflitos[i][0]) && (atribuido(atribuicoes, num_items, conflitos[i][1]) == 1) && (existe_par(triangulos, num_items, heroi_conflito, conflitos[i][1]) == 0))
        {
            if ((eh_conflito(heroi_inicial, conflitos[i][1], conflitos, num_conflitos)) && (existe_par(triangulos, num_items, heroi_inicial, conflitos[i][1]) == 0))
            {
                printf("Coloca %d %d %d\n", heroi_inicial, heroi_conflito, conflitos[i][1]);
                triangulos[indiceAtual].x = heroi_inicial;
                triangulos[indiceAtual].y = heroi_conflito;
                triangulos[indiceAtual].z = conflitos[i][1];
                return 1;
            }
        }
        else if ((heroi_conflito == conflitos[i][1]) && (atribuido(atribuicoes, num_items, conflitos[i][0]) == 1) && (existe_par(triangulos, num_items, heroi_conflito, conflitos[i][0]) == 0))
        {
            if ((eh_conflito(heroi_inicial, conflitos[i][0], conflitos, num_conflitos)) && (existe_par(triangulos, num_items, heroi_inicial, conflitos[i][0]) == 0))
            {
                printf("Coloca %d %d %d\n", heroi_inicial, heroi_conflito, conflitos[i][0]);
                triangulos[indiceAtual].x = heroi_inicial;
                triangulos[indiceAtual].y = heroi_conflito;
                triangulos[indiceAtual].z = conflitos[i][0];
                return 1;
            }
        }
    }
    return 0;
}

int conta_triangulo(int heroi_inicial, int **conflitos, int num_conflitos, int *atribuicoes, int num_items, Triangulo *triangulos)
{
    int i;
    int qnt_triangulo = 0;
    for (i = 0; i < num_conflitos; i++)
    {
        if ((heroi_inicial == conflitos[i][0]) && (atribuido(atribuicoes, num_items, conflitos[i][1]) == 1) && (existe_par(triangulos, num_items, heroi_inicial, conflitos[i][1]) == 0))
        {
            qnt_triangulo += eh_triangulo(heroi_inicial, conflitos[i][1], conflitos, num_conflitos, atribuicoes, num_items, i, triangulos);
        }
        else if ((heroi_inicial == conflitos[i][1]) && (atribuido(atribuicoes, num_items, conflitos[i][0]) == 1) && (existe_par(triangulos, num_items, heroi_inicial, conflitos[i][0]) == 0))
        {
            qnt_triangulo += eh_triangulo(heroi_inicial, conflitos[i][0], conflitos, num_conflitos, atribuicoes, num_items, i, triangulos);
        }
    }
    return qnt_triangulo;
}

int escolhe_heroi(int **conflitos, int num_conflitos, int *atribuicoes, int num_items)
{
    int i;
    int super_heroi;
    int qtde_triangulos = 0;
    Triangulo *triangulos = (Triangulo *)calloc(num_items, sizeof(Triangulo));

    for (i = 0; i < num_items; i++)
    {
        if (atribuicoes[i] != 0)
        {
            super_heroi = atribuicoes[i];
            qtde_triangulos += conta_triangulo(super_heroi, conflitos, num_conflitos, atribuicoes, num_items, triangulos);
        }
    }
    int tamanhoTriangulos = ultima_posicao(triangulos, num_items);
    for (i = 0; i < tamanhoTriangulos; i++)
    {
        printf("\n\nTRIANGULO: %d %d %d\n\n", triangulos[i].x, triangulos[i].y, triangulos[i].z);
    }
    free(triangulos);
    return qtde_triangulos;
}
