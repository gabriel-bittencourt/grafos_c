#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../graph.h"

/* 
    Implementação do Algoritmo Bellman-Ford para cálculo dos caminhos de menor peso em um grafo direcionado
    com aresta com pesos positivos ou negativos.

    Entrada: Grafo direcionado G conexo; Vértice s inicial
    Saída: Caminhos de menor pesos e seus respectivos pesos

    Primeiro, inicializa-se os vetores auxiliares de tamanho |V|,
    e então, o algoritmo percorre todos os vértices |V|-1 vezes, verificando todas as arestas a cada passo.
    
    Complexidade: O(VE)
*/

void bellman_ford(Graph* g, vertex s){

    // Inicialização dos vetores auxiliares
    int* dist = (int*) malloc( g->N * sizeof(int) );
    int* parent = (int*) malloc( g->N * sizeof(int) );

    for (vertex v = 0; v < g->N; v++){
        dist[v] = INT_MAX; // Todos vértices recebem custo máximo
        parent[v] = -1;    // Todos os vértices não tem predecessor
    }
    dist[s] = 0; // O vértice inicial recebe custo zero

    // Percorre todas as arestas do grafo |V|-1 vezes
    for (int i = 1; i < g->N; i++){

        // Para cada vértice
        for (vertex v = 0; v < g->N; v++){
            
            // Visita cada aresta de v
            for (
                Node* w = g->adj[v].head;
                w;
                w = w->next
            ){
                
                // Se a novo peso é menor que o atual
                if( dist[w->dest] > dist[v] + w->weight ){

                    // Atualiza o peso de w
                    dist[w->dest] = dist[v] + w->weight;

                    // v é o atual pai de w no caminho
                    parent[w->dest] = v;
                    
                }

            }

        }

    }

    printf("\nMelhores caminhos a partir do vértice %d:\n\n", s);

    // Imprime os resultados
    print_paths(g, dist, parent);
}


// Exemplo
int main(){

    Graph* g = new_graph(6);

    add_edge(g, 0, 1, -10, 1);
    add_edge(g, 0, 2,   5, 1); 
    add_edge(g, 1, 3,   1, 1);
    add_edge(g, 2, 1,  -3, 1);
    add_edge(g, 2, 3,  -8, 1);
    add_edge(g, 2, 4,   2, 1);
    add_edge(g, 3, 4,  20, 1);
    add_edge(g, 3, 5,   4, 1);
    add_edge(g, 4, 5,  -6, 1);

    printf("Grafo direcionado com arestas com pesos:\n");
    printf("| v | -> (w | peso)\n\n");
    print_graph(g);

    vertex s = 0;

    bellman_ford(g, s);

    return 0;
}
