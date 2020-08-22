#include <stdio.h>
#include <stdlib.h>

#include "../graph.h"
#include "../data-structures/disjoint-set.c"


/* 
    Implementação do Algoritmo de Kruskal para cálculo de uma árvore (ou floresta) de custo mínimo

    Entrada: Grafo G não direcionado
    Saída: Uma árvore geradora de custo mínimo e o peso total mínimo

    O algoritmo foi implementado utilizando duas estruturas auxiliares.

        Estrutura Edge, para qualificar e ordenar as arestas do grafo.
            A ordenação das arestas tem complexidade O(ElgE)

        Estrutura de disjoint-set com compressão de caminho e união por rank

    Complexidade: O(ElgV)
*/

                          
/*    Estrutura auxiliar para ordenação das arestas por peso */
typedef struct{
    vertex v;
    vertex w;
    int weight;
} Edge;

// Seleciona as arestas de g
Edge* get_edges(Graph* g){

    // Vetor de arestas
    Edge* edges = (Edge*) malloc( g->M * sizeof(Edge));

    // Auxiliar
    Edge e;

    // Vetor auxiliar com vértices que já tiveram todos as arestas selecionadas
    // Como g é um grafo não direcionado, impede que a aresta seja selecionada se a 
    // aresta na direção contrária já foi selecionada
    int* visited = (int*) calloc( g->N, sizeof(int) );

    // Inicializa o vetor de arestas
    int j = 0;
    for (vertex v = 0; v < g->N; v++){
        
        e.v = v;

        for (
            Node* w = g->adj[v].head;
            w;
            w = w->next
        ){

            if( visited[w->dest] == 0 ){
                e.w = w->dest;
                e.weight = w->weight;

                edges[j++] = e;
            }
        }

        visited[v] = 1;

    }
    
    return edges;
}

// Procedimento de merge do merge sort
void merge_edges(Edge* edges, int l, int m, int r){

    int a = l;
    int b = m+1;
    int c = 0;

    Edge* temp = (Edge*) malloc( (r - l + 1) * sizeof(int));

    while(a <= m && b <= r ){

        
        if( edges[a].weight < edges[b].weight )
            temp[c++] = edges[a++];
        else
            temp[c++] = edges[b++];

    }

    while(a < m+1)
        temp[c++] = edges[a++];

    while(b < r+1)
        temp[c++] = edges[b++];


    for (int i = l; i < r+1; i++)
        edges[i] = temp[i-l];

}

// Algoritmo de merge sort
void merge_sort_edges(Edge* edges, int l, int r){
    
    if (l < r){
        int m = (l+r-1)/2;

        merge_sort_edges(edges, l, m);
        merge_sort_edges(edges, m+1, r);

        merge_edges(edges, l, m, r);
    }
}

// Ordena as arestas de g em ordem crescente
Edge* sort_edges(Graph* g){

    // Seleciona as arestas de g
    Edge* edges = get_edges(g);

    // Aplicação do merge sort
    merge_sort_edges(edges, 0, g->M - 1);
    
    return edges;
}

/*------------------------------------------------------------*/


// Algoritmo de Kruskal
Graph* kruskal(Graph* g){

    // Ordenação das arestas por peso
    Edge* edges = sort_edges(g);

    // Disjoint-set para manter os vértices já conexos
    DisjointSet* vertices = new_disjoint_set(g->N);
    
    // Árvore (ou floresta) de mínimo custo que será gerada
    Graph* t = new_graph(g->N);

    // Peso total da árvore geradora de custo mínimo
    int total = 0;


    // Para cada aresta
    for (int i = 0; i < g->M; i++){
        
        // A aresta escolhida é sempre a menor aresta possível, já que o vetor está ordenado
        Edge edge = edges[i];

        // Se v e w ainda não são conectados
        if( find_set(vertices, edge.v)  !=  find_set(vertices, edge.w)  ){

            // Conecta os vértices
            union_set(vertices, edge.v, edge.w);

            // Adiciona o vértice na árvore geradora
            add_edge(t, edge.v, edge.w, edge.weight, 0);

            // Atualiza o peso total
            total += edge.weight;

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

    kruskal(g);

    return 0;
}
