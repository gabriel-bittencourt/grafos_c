#include <stdio.h>
#include <stdlib.h>

#include "../graph.h"

// Procedimento recursivo de busca em profundidade
// Parâmetros:
// Grafo, vértice atual, vetor de visitados, árvore de profundidade gerada 
void DFS_procedure(Graph* g, vertex v, int* visited, Digraph* t){

    // Imprime o vértice atual
    printf("%d ", v);

    // Marca v
    visited[v] = 1;

    // Para cada vértice w adjacente a v
    for (
        Node* w = g->adj[v].head;
        w;
        w = w->next
    ){
        // Se w é não marcado
        if( visited[w->dest] == 0 ){

            // Insere a aresta na árvore
            add_edge(t, v, w->dest, 0, 1);
            
            DFS_procedure(g, w->dest, visited, t);
        }
    }


}


// Percorre em profundidade a partir do vértice v
// Retorna uma árvore de profundidade de g com raiz em v
Digraph* DFS(Graph* g, vertex v){

    // Vetor de vértices marcados
    // Inicializa como não marcados
    // visited[v] == 0  -> v é não marcado
    // visited[v] == 1  -> v é marcado
    int* visited = (int*) calloc( g->N, sizeof(int) );

    // Inicializa vetor dos pais dos vértices
    // Ex.: parent[v] == w  ->  o vértice w é o pai de v na árvore gerada
    int* parent = (int*) malloc( g->N * sizeof(int) );
    for (int i = 0; i < g->N; i++) parent[i] = -1; 

    // Árvore de profundidade que será gerada
    Digraph* t = new_graph(g->N);

    printf("\nBusca em profundidade com raiz em %d\n\n", v);
    printf("Ordem da busca: ");

    DFS_procedure(g, v, visited, t);

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

    Digraph* t = DFS(g, root);

    printf("\nÁrvore de profundidade gerada:\n");
    print_graph(t);
    printf("\n");

    return 0;
}
