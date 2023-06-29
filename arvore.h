#ifndef ARVORE_H
#define ARVORE_H

typedef struct Node
{
    int *grupoA;
    int *grupoB;
    int conflitos;  // Número de conflitos para a atribuição atual
    int afinidades; // Número de afinidades para a atribuição atual
    struct Node *esquerda;
    struct Node *direita;  
} Node;

Node *cria_nodo(int conflitos, int afinidades, int *grupoA, int *grupoB, int num_itens);

int conta_nos(Node *root);

void exibe_arvore(Node *root);

void free_node(Node *node);

void free_tree(Node *root);

#endif