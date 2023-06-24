#ifndef ARVORE_H
#define ARVORE_H

typedef struct Node {
    int nivel;          // Nível do nó na árvore
    // int* assignment;    // Atribuição de grupos para cada item
    int *grupoA;
    int *grupoB;
    int conflitos;      // Número de conflitos para a atribuição atual
    // int upperBound;     // Limite superior (Upper Bound) para a função objetivo
    struct Node* esquerda;  // Nó filho esquerdo
    struct Node* direita; // Nó filho direito
} Node;

Node* cria_nodo(int conflitos, int *grupoA, int *grupoB);

void free_node(Node* node);

void free_tree(Node* root);

#endif