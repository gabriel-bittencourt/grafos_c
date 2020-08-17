#include <stdio.h>
#include <stdlib.h>

#include "../graph.h"

// Percorre em largura a partir do vértice v
// Retorna uma árvore de largura de g com raiz em v
Digraph* BFS(Graph* g, vertex v){

    // Vetor de vértices marcados
    // Inicializa como não marcados
    // visited[v] == 0  -> v é não marcado
    // visited[v] == 1  -> v é marcado
    int* visited = (int*) calloc( g->N, sizeof(int) );
    
    // Fila de vértices alcançados
    int* queue = (int*) malloc( g->N * sizeof(int) );
    int front = 0, back = 1;

    // Árvore de largura que será gerada
    Digraph* t = new_graph(g->N);

    // Marca v
    visited[v] = 1;

    printf("\nBusca em largura com raiz em %d\n\n", v);
    printf("Ordem da busca: %d", v);

    // Enquando houver vértices na fila
    while( front < g->N - 1 ){
        
        // Visita cada aresta de v
        for (
            Node* w = g->adj[v].head;
            w;
            w = w->next
        ){

            // Se w não for marcado
            if( visited[w->dest] == 0 ){
                
                // Marca w
                visited[w->dest] = 1;

                // Adiciona w na fila
                queue[back++] = w->dest;

                // Adiciona a aresta à árvore
                add_edge(t, v, w->dest, 0, 1);
                

                printf(" %d", w->dest);
            }
        }

        // Seleciona o próximo vértice da fila
        v = queue[++front];
    }

    printf("\n");

    return t;
}

// Exemplo
int main(){

    Graph* g = new_graph(9);
    add_edge(g, 0, 1, 0, 0);
    add_edge(g, 0, 2, 0, 0);
    add_edge(g, 2, 3, 0, 0);
    add_edge(g, 2, 5, 0, 0);
    add_edge(g, 2, 7, 0, 0);
    add_edge(g, 3, 4, 0, 0);
    add_edge(g, 4, 6, 0, 0);
    add_edge(g, 5, 6, 0, 0);
    add_edge(g, 6, 7, 0, 0);
    add_edge(g, 7, 8, 0, 0);

    printf("Grafo:\n");
    print_graph(g);

    vertex root = 0;

    Digraph* t = BFS(g, root);

    printf("\nÁrvore de largura gerada:\n");
    print_graph(t);
    printf("\n");


    return 0;
}
