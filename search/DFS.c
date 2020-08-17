#include <stdio.h>
#include <stdlib.h>

#include "../graph.h"

// Procedimento recursivo de busca em profundidade
// Parâmetros:
// Grafo, vértice atual, vetor de visitados, vetor de pais, ordem de visita, contador, articulações, vetor low (auxiliar), árvore gerada 
void DFS_procedure(Graph* g, vertex v, int* visited, int* parent, int* disc, int* counter, int* art, int* low, Digraph* T){

    // Imprime o vértice atual
    printf("%d ", v);

    // Marca v
    visited[v] = 1;

    // Salva o momento em que v foi alcançado e incrementa o contador;
    disc[v] = low[v] = (*counter)++;

    // Calcula o número de filhos de v
    int children = 0;

    // Para cada vértice w adjacente a v
    for (
        Node* w = g->adj[v].head;
        w;
        w = w->next
    )
    {
        // Incrementa o contador de filhos
        children++;

        // Se w é não marcado
        if( visited[w->dest] == 0 ){
            parent[w->dest] = v;
            add_edge(T, v, w->dest, 0, 1);
            DFS_procedure(g, w->dest, visited, parent, disc, counter, art, low, T);

            // Verifica se o low de algum filho de v é menor que o low de v
            // low[v] = min( low[w], low[v] )
            low[v] = ( low[w->dest] < low[v] ) ? low[w->dest] : low[v];


            // v é uma articulação se, e somente se, v satisfaz uma das condições abaixo

            // v é a raiz e tem mais de um filho
            if( parent[v] == -1 && children > 1 ){
                art[v] = 1;
            }

            // v não é raiz e low[w] >= disc[v]
            if ( parent[v] != -1 && low[w->dest] >= disc[v] ){
                art[v] = 1;
            }

        }

        // Se w é marcado
        else {
            // Se w não é pai de v, então vw é uma aresta de retorno
            if( parent[v] != w->dest )
                low[v] = ( low[v] < disc[w->dest] ) ? low[v] : disc[w->dest];
            
        }
    }

}

// Percorre em profundidade a partir do vértice v
// Retorna uma árvore de profundidade de g com raiz em v
// Calcula as articulações (vértices de corte)
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

    // Vetor da do momento em que cada vértice foi descoberto
    // Ex.: disc[v] == 3  ->  v foi o 4º vértice alcançado
    // Se disc[v] < disc[w], então v está mais próximo da raiz que w
    int* disc = (int*) malloc( g->N * sizeof(int) );
    
    // Variável auxiliar para facilitar a contagem
    int counter = 0;

    /* 
        Vetor auxiliar para cálculo das articulações
        low[v] == disc(w)  ->  w é o vértice mais próximo da raiz que pode ser alcançado a partir de v
        utilizando apenas uma aresta de retorno que leva de v ou de algum descendente de v para w
        na árvore de profundidade gerada
        Ex.:
               raiz
               /  \
              w   
             / \
            v 
           /
          u
        Se há uma aresta de retorno entre u e w, e não há nenhuma aresta de retorno de u ou de
        algum descendente de u para w ou para algum ancestral de w, então uw é um aresta de retorno e
        low[u] = low[v] = disc(w)
        Nesse caso, w é uma articulação
    */
    int* low = (int*) malloc( g->N * sizeof(int) );

    // Vetor de articulações
    int* art = (int*) calloc( g->N, sizeof(int) );

    // Árvore de profundidade que será gerada
    Digraph* t = new_graph(g->N);

    printf("\nBusca em profundidade com raiz em %d\n\n", v);
    printf("Ordem da busca: ");

    // Chamada ao procedimento recursivo de busca em profundidade
    DFS_procedure(g, v, visited, parent, disc, &counter, art, low, t);
    
    // Imprime as articulações do grafo
    printf("\n\nArticulações: ");
    for (int i = 0; i < g->N; i++)
    {
        if(art[i])
            printf("%i ", i);
    }
    printf("\n");
    //

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
