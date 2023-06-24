#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

Node* cria_nodo(int conflitos, int *grupoA, int *grupoB) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->conflitos = conflitos;
    node->grupoA = grupoA;
    node->grupoB = grupoB;
    node->esquerda = NULL;
    node->direita = NULL;
    return node;
}

void free_node(Node* node) {
    free(node);
}

void free_tree(Node* root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->esquerda);
    free_tree(root->direita);
    free_node(root);
}