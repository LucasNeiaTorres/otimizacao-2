#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

Node* cria_nodo(int conflitos, int *grupoA, int *grupoB, int num_itens) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->conflitos = conflitos;
    node->grupoA = (int*)calloc(num_itens, sizeof(int));
    node->grupoB = (int*)calloc(num_itens, sizeof(int));
    memcpy(node->grupoA, grupoA, num_itens * sizeof(int));
    memcpy(node->grupoB, grupoB, num_itens * sizeof(int));
    node->esquerda = NULL;
    node->direita = NULL;
    return node;
}

void exibe_arvore(Node* root) {
    if (root == NULL) 
        return;

    printf("Conflitos: %d\n", root->conflitos);
    printf("Grupo A: ");
    for (int i = 0; root->grupoA[i] != 0; i++) 
        printf("%d ", root->grupoA[i]);
    
    printf("\nGrupo B: ");
    for (int i = 0; root->grupoB[i] != 0; i++) 
        printf("%d ", root->grupoB[i]);

    printf("\n--------------------------------\n");
    exibe_arvore(root->esquerda);
    exibe_arvore(root->direita);
}

void free_node(Node* node) {
    free(node->grupoA);
    free(node->grupoB);
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