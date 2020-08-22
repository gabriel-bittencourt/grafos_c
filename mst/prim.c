#include <stdio.h>
#include <stdlib.h>

#include "../graph.h"
#include "../data-structures/min-heap.c"

/*
    Implementação do Algoritmo de Prim para cálculo de uma árvore de custo mínimo

    Entrada: Grafo G não direcionado conexo
    Saída: Uma árvore geradora de custo mínimo e o peso total mínimo
    
    O algoritmo foi implementado utilizando um heap binário de mínimo auxiliar.
    
    Complexidade: O(ElgV)
*/

Graph* prim(Graph* g, vertex r){
 
    // Inicializa Heap auxiliar para escolha do próximo vértice
    Heap* h = new_heap(g->N);

    // Atualiza o vetor de posições
    swap( &( h->index_of[0] ), &( h->index_of[r] ) );
        
    // Coloca o vértice v no topo do Heap
    swap( &( h->vertices[ 0 ] ), &( h->vertices[ r ] ) );

    // O peso mínimo do vetor inicial é zero
    h->dist[r] = 0;
    
    // O heap inicial tem todos os vértices do grafo com peso máximo, exceto v que tem peso zero
    h->size = g->N;

    // Ponteiro auxiliar para o vetor dos pesos atuais dos vértices
    int* dist = h->dist;

    // Vetor com os pais dos vértices no melhor caminho
    // Se o melhor caminho de v para w é  v -> x -> w
    // Então:
    //     parent[w] == x
    //     parent[x] == v
    //     parent[v] == -1
    vertex* parent = (int*) malloc( g->N * sizeof(int) );

    // Inicializa o vetor de pais
    for (vertex i = 0; i < g->N; i++)
        parent[i] = -1;

    
    // Vetor com vértices fechados
    // Um vértice é fechado quando já sabe-se qual aresta o liga à árvore
    vertex* closed = (int*) calloc( g->N, sizeof(int) );

    // Seleciona o primeiro vértice
    vertex v = pop_heap(h);

    // Enquanto o Heap não estiver vazio
    while ( h->size != 0 ){

        // Visita cada aresta de v
        for (
            Node* w = g->adj[v].head;
            w;
            w = w->next
        ){

            // Se o vértice não está fechado E se o peso da aresta atual é menor que o peso atual
            if( closed[w->dest] == 0 && w->weight < dist[w->dest] ){

                // v é o atual pai de w na árvore
                parent[w->dest] = v;

                // Atualiza o peso de w
                decrease_dist(h, w->dest, w->weight);

            }

        }

        // Fecha o vértice v
        closed[v] = 1;

        // Retira o próximo vértice do heap (Sempre o atual vértice de menor peso)
        v = pop_heap(h);

    }


    // Árvore de mínimo custo que será gerada
    Graph* t = new_graph(g->N);

    // Peso total da árvore geradora de custo mínimo
    int total = 0;

    // Constrói a árvore a partir dos vetores de pais e de pesos
    for (vertex v = 0; v < g->N; v++){
        
        // Se v não é a raiz do caminho
        if( parent[v] != -1 ){

            // Adiciona uma aresta não direcionada entre v e o pai de v
            add_edge(t, v, parent[v], dist[v], 0);

            // Atualiza o peso total
            total += dist[v];

        }

    }
    

    printf("\nÁrvore de custo mínimo gerada:\n");
    print_graph(t);

    printf("\nCusto mínimo total: %d\n\n", total);

    return t;

}


// Exemplo
int main(){
    
    Graph* g = new_graph(6);

    add_edge(g, 0, 1, 10, 0);
    add_edge(g, 0, 2, 5,  0); 
    add_edge(g, 1, 3, 1,  0);
    add_edge(g, 2, 1, 3,  0);
    add_edge(g, 2, 3, 8,  0);
    add_edge(g, 2, 4, 2,  0);
    add_edge(g, 3, 4, 4,  0);
    add_edge(g, 3, 5, 4,  0);
    add_edge(g, 4, 5, 6,  0);


    printf("Grafo não direcionado com arestas com pesos:\n");
    printf("| v | -> (w | peso)\n\n");
    print_graph(g);

    vertex r = 0;

    prim(g,  r);

    return 0;
}
