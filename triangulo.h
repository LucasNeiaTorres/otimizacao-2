#ifndef TRIANGULO_H
#define TRIANGULO_H

typedef struct Triangulo{
    int x;
    int y;
    int z;
}Triangulo;

int insereTriangulo(Triangulo *triangulos, int num_items, int heroi_x, int heroi_y, int heroi_z);

int eh_conflito(int x, int y, int **conflitos, int num_conflitos);

int atribuido(int *atribuicoes, int num_items, int super_heroi);

int ultima_posicao(Triangulo *triangulos, int num_items);

int existe_par(Triangulo *triangulos, int num_items, int x, int y);

int eh_triangulo(int heroi_inicial, int heroi_conflito, int **conflitos, int num_conflitos, int *atribuicoes, int num_items, int posicao, Triangulo *triangulos);

int conta_triangulo(int heroi_inicial, int **conflitos, int num_conflitos, int *atribuicoes, int num_items, Triangulo *triangulos);

int escolhe_heroi(int **conflitos, int num_conflitos, int *atribuicoes, int num_items);

#endif