#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int parent;
    int rank;
} DisjointSetNode;

typedef DisjointSetNode* DisjointSet;

// Cria um disjoint-set de tamanho N
DisjointSet* new_disjoint_set(int N){

    // DisjointSet* é um vetor de DisjointSet
    // DisjointSet é um ponteiro para um DisjointSetNode
    /*
        sets: [0, 1, 2, 3, ... , N-1]
               |
         (parent, rank)
    */
    DisjointSet* sets = (DisjointSet*) malloc(N * sizeof(DisjointSetNode*));

    // Inicializa os subconjuntos
    for (int i = 0; i < N; i++){

        sets[i] = (DisjointSetNode*) malloc(sizeof(DisjointSetNode));
        sets[i]->parent = i;  // Cada nó é pai de si mesmo
        sets[i]->rank = 0;    // Cada nó tem rank 0
    }
    
    return sets;

}

// Operação de FindSet com compressão de caminho
DisjointSetNode* find_set(DisjointSet* sets, int x){

    DisjointSetNode* nodeX = sets[x];

    // Percorre o caminho do nó até a raiz, aplicando a compressão de caminho
    if( nodeX->parent != x )
        nodeX->parent = find_set(sets, nodeX->parent)->parent;

    // Retorna o representante do conjunto
    return sets[nodeX->parent];
}

// Une dois subconjuntos pelo critério de união por rank
void union_set(DisjointSet* sets, int x, int y){

    // Seleciona as raízes dos conjuntos
    DisjointSetNode* root_x = find_set(sets, x);
    DisjointSetNode* root_y = find_set(sets, y);

    // Faz root_x ser a raíz de menor rank
    if( root_x->rank > root_y->rank ){
        DisjointSetNode* temp = root_x;
        root_x = root_y;
        root_y = temp;
    }

    // Faz a raiz do conjunto de y ser pai da raiz do conjunto de x
    // Se ambos fazem parte do mesmo conjunto, root_x e root_y são iguais
    root_x->parent = root_y->parent;

    // Se ambos tinham o mesmo rank, atualiza o rank da raiz de y
    if( root_x->rank == root_y->rank )
        root_y->rank++;

}

// Imprime os subconjuntos
void print_set(DisjointSet* sets, int N){

    for (int i = 0; i < N; i++){
        
        printf("%d <-", i);

        for (int j = 0; j < N; j++){
    
            if (find_set(sets, j)->parent == i)
                printf(" %2d", j);

            }

        printf("\n");
    }
    printf("\n");
}
