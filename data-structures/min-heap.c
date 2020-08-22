#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Estrutura de um Heap binário de mínimo adaptado
typedef struct {

    int size;          // Tamanho atual do heap
    int N;             // Tamanho máximo do heap

    int* vertices;     // Vetor dos vértices
    int* dist;         // Vetor dos pesos
    int* index_of;     // Vetor com as posições atuais dos vértices no heap
} Heap;

// Cria novo heap de tamanho N
Heap* new_heap(int N){

    Heap* new = (Heap*) malloc( sizeof(Heap) );
    new->N = N;
    new->size = 0;
    
    new->vertices = (int*) malloc( N * sizeof(int) );    
    new->dist = (int*) malloc( N * sizeof(int) );
    new->index_of = (int*) malloc( N * sizeof(int) );

    // Inicializa os vetores
    for (int i = 0; i < N; i++){
        new->vertices[i] = i;     // Insere os vértices na ordem
        new->index_of[i] = i;
        new->dist[i] = INT_MAX;   // Todos os vértices tem peso MAX
    }
    
    return new;
}

// Retorna a posição do pai de i
int parent(int i){
    return (i - 1) / 2;
}

// Retorna a posição do filho da esquerda de i
int left(int i){
    return (2 * i) + 1;
}

// Retorna a posição do filho da direita de i
int right(int i){
    return (2 * i) + 2;
}

// Troca o conteúdo de dois elementos do heap
void swap(int* x, int* y){
    
    int temp = *x;
    *x = *y;
    *y = temp;

}

// Imprime a árvore atual (em formato de vetor)
void print_heap(Heap* h){

    for (int i = 0; i < h->size; i++){
        printf(" (%2d|%2d)", h->vertices[i], h->dist[ h->vertices[i] ]);
    }
    printf("\n\n");

}

// Método para normalizar a árvore (Todo pai deve ter valor menor que os filhos)
// Nesse método, pressupõe-se que as sub-árvores dos filhos da raiz passada já estão normalizados
// i é a posição da raiz da sub-árvore
void heapify(Heap* h, int i){

    // Posição e peso do filho da esquerda
    int l = left(i);
    int l_dist = h->dist[ h->vertices[l] ];
 
    // Posição e peso do filho da direita
    int r = right(i);
    int r_dist = h->dist[ h->vertices[r] ];

    // Auxiliar para selecionar o filho
    int smallest = i;

    // Seleciona o filho de menor peso
    if( l < h->size && l_dist < h->dist[ h->vertices[ smallest ] ] )
        smallest = l;
    if( r < h->size && r_dist < h->dist[ h->vertices[ smallest ] ] )
        smallest = r;
 
    // Se existe um filho menor que o pai
    if (smallest != i){

        // Atualiza o vetor de posições
        swap( 
            &( h->index_of[ h->vertices[smallest] ] ),
            &( h->index_of[ h->vertices[i] ] )
        );

        // Troca a raiz com o filho de menor peso
        swap( &( h->vertices[i] ), &( h->vertices[smallest] ) );

        // Chama recursivamente para subárvore
        heapify(h, smallest);
    }
}

 // Remove o menor elemento do heap (Sempre a raiz)
int pop_heap(Heap* h){

    // Salva o valor da raiz atual
    int root = h->vertices[0];

    // Se a árvore só tem um elemento
    if (h->size == 1){
        h->size--;
        return root;
    }

    // Atualiza o vetor de posições
    swap(
        &( h->index_of[ h->vertices[h->size - 1] ] ),
        &( h->index_of[ root ] )
    );

    // Inverte o menor elemento com o último elemento
    swap( &(h->vertices[0]), &( h->vertices[h->size - 1] ) );

    // Diminui o tamanho do heap
    h->size--;

    // Normaliza a árvore
    heapify(h, 0);

    return root;
}

// Atualiza o peso atual de um vértice (O novo peso sempre será menor que o atual)
void decrease_dist(Heap* h, int v, int new_dist){ 

    // Posição de v no heap
    int i = h->index_of[v];

    // Atualiza o peso de v
    h->dist[v] = new_dist;

    // Vértice pai de v
    int parent_v = h->vertices[ parent(i) ];

    // Enquanto i não for a raiz E o peso do pai for menor que o peso do filho
    while( i != 0 &&  h->dist[ parent_v ] > h->dist[v] ){

        // Atualiza o vetor de posições
        swap( &( h->index_of[v] ), &( h->index_of[parent_v] ) );
        
        // Troca o pai com o filho
        swap( &( h->vertices[ parent(i) ] ), &( h->vertices[ i ] ) );

        // Repete o processo com o pai
        i = parent(i);
        parent_v = h->vertices[ parent(i) ];
    }

}
