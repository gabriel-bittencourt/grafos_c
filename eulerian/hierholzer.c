#include <stdio.h>
#include <stdlib.h>

#include "../graph.h"

// Algoritmo DFS modificado para cálculo de caminhos eulerianos em grafos direcionados
// Parâmetros: Grafo direciano, vértice inicial, vetor de graus de saída
void hierholzer_DFS(Digraph* d, vertex v, int* out){

    // Auxiliar
    vertex w;

    // Enquanto v ainda tem arestas de saída
    while( out[v] > 0 ){

        // Retira uma aresta de v para w e decrementa o contador arestas de saída de v
        w = pop_edge(d, v);
        out[v]--;

        // Visita w
        hierholzer_DFS(d, w, out);
    }

    // v não tem arestas de saída
    printf(" %d ", v);
    
}

// Algoritmo de Hierholzer para cálculo de caminhos e ciclos eulerianos em grafos direcionados
void hierholzer(Digraph* d){

    int* in = (int*) calloc( d->N, sizeof(int) );
    int* out = (int*) calloc( d->N, sizeof(int) );

    // Para cada vértice v
    for (int v = 0; v < d->N; v++){

        // Para cada aresta divergente a v
        for (   Node* w = d->adj[v].head;
                w;
                w = w->next
        ){
            in[w->dest]++;
            out[v]++;
        }

    }

    // Vértice inicial do caminho
    vertex start;

    // Número de vértices com grau de saída maior que grau de entrada
    int start_nodes = 0;

    // Número de vértices com grau de entrada maior que grau de saída
    int end_nodes = 0;

    // Calcula o vértice inicial do caminho
    for (int v = 0; v < d->N; v++){
        
        // Verifica se o grafo tem um vértice com grau de saída maior que grau de entrada
        // Nesse caso, o vértice v é o único início possível
        if( out[v] - in[v] == 1 ){
            start = v;
            start_nodes++;
        } 
        // Verifica se o grafo tem um vértice com grau de entrada maior que grau de saída
        else if ( in[v] - out[v] == 1 )
            end_nodes++;
        
        // Se não há vértices de início, qualquer vértice com aresta de saída pode ser o inicío
        else if( start_nodes == 0 && out[v] > 0 )
            start = v;

        // Grafo não pode ser nem euleriano nem semi-euleriano
        if( start_nodes > 1 || end_nodes > 1 )
            break;   

    }

    // Verifica se grafo é Euleriano, Semi-Euleriano ou Não Euleriano
    if ( start_nodes == 0 && end_nodes == 0 ){
        printf("\nGrafo Euleriano");
    }
    else if ( start_nodes == 1 && end_nodes == 1 ){
        printf("\nGrafo Semi-Euleriano");
    }
    else{
        printf("\nGrafo Não Euleriano");
        return;
    }
    
    // Copia o grafo
    Digraph* c = copy_graph(d);

    printf("\nCaminho no sentido reverso iniciando em %d:\n", start);

    // Chamada ao procedimento recursivo
    hierholzer_DFS(c, start, out);

    printf("\n\n");

}

// Exemplo
int main(){

    Digraph* d = new_graph(5);
    add_edge(d, 0, 1, 0, 1);
    add_edge(d, 1, 3, 0, 1);
    add_edge(d, 1, 2, 0, 1);
    add_edge(d, 2, 0, 0, 1);
    add_edge(d, 3, 4, 0, 1);
    add_edge(d, 4, 1, 0, 1);

    printf("Grafo direcionado: \n");
    print_graph(d);

    hierholzer(d);

    return 0;
}
