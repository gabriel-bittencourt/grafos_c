#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../graph.h"
#include "../data-structures/min-heap.c"

/* 
    Implementação do Algoritmo de Dijkstra para cálculo dos caminhos de menor peso em um grafo com aresta de pesos positivos

    Entrada: Grafo G conexo; Vértice v inicial
    Saída: Caminhos de menor pesos e seus respectivos pesos

    O algoritmo foi implementado utilizando um Heap binário de mínimo para escolha do próximo vértice de menor peso.
            
    Complexidade: O(ElogV)

*/

void dijkstra(Graph* g, vertex v){

    // Inicializa Heap auxiliar para escolha do próximo vértice
    Heap* h = new_heap(g->N);

    // Atualiza o vetor de posições
    swap( &( h->index_of[0] ), &( h->index_of[v] ) );
        
    // Coloca o vértice v no topo do Heap
    swap( &( h->vertices[ 0 ] ), &( h->vertices[ v ] ) );

    // A distância até o vetor inicial é zero
    h->dist[v] = 0;
    
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


    printf("\nMelhores caminhos a partir do vértice %d:\n\n", v);

    
    // Se o vértice de menor peso tem peso MAX, então esse vértice não pode ser alcançado a partir do vértice inicial fornecido
    // Como esse é o menor vértice, todos outros vértices restantes também tem peso MAX,
    // logo não há mais vértices alcançáveis a partir do vértice inicial
    // Nesse caso, encerra-se a execução do algoritmo

    // Enquando o Heap não estiver vazio E
    // Enquanto o vértice de menor peso não tem peso MAX
    while ( h->size != 0 && dist[v] < INT_MAX){

        // Visita cada aresta de v
        for (
            Node* w = g->adj[v].head;
            w;
            w = w->next
        ){

            // Se a novo peso é menor que o atual
            if( dist[v] + w->weight < dist[w->dest] ){

                // v é o atual pai de w no caminho
                parent[w->dest] = v;

                // Atualiza o peso de w
                decrease_dist(h, w->dest, dist[v] + w->weight);

            }
        
        }
  
        // Retira o próximo vértice do heap (Sempre o atual vértice de menor peso)
        v = pop_heap(h);

    }

    // Imprime os resultados
    print_paths(g, dist, parent);

}


// Exemplo
int main(){

    Graph* g = new_graph(6);

    add_edge(g, 0, 1, 10, 1);
    add_edge(g, 0, 2,  5, 1); 
    add_edge(g, 1, 3,  1, 1);
    add_edge(g, 2, 1,  3, 1);
    add_edge(g, 2, 3,  8, 1);
    add_edge(g, 2, 4,  2, 1);
    add_edge(g, 3, 4,  4, 1);
    add_edge(g, 3, 5,  4, 1);
    add_edge(g, 4, 5,  6, 1);


    printf("Grafo direcionado com arestas com pesos:\n");
    printf("| v | -> (w | peso)\n\n");
    print_graph(g);

    int v = 0;

    dijkstra(g, v);

    return 0;
}
