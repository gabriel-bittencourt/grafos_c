#include <stdio.h>
#include <stdlib.h>

#include "../graph.h"

// Procedimento recursivo para encontrar próxima aresta do caminho euleriano
void fleury_next_edge(Graph* g, vertex v, int* degrees){

    // Se um vértice de grau zero foi alcançado, então esse vértice é o fim do caminho
    if( degrees[v] == 0 )
        return;

    // Auxiliar
    vertex w;

    // v só tem uma aresta v-w
    if ( degrees[v] == 1 ){
        
        // printf("\t\tO %d só tem 1 aresta\n", v);

        // Remove a única aresta de v
        w = pop_edge(g, v);
        degrees[v]--;

        // v não faz mais parte do caminho
        g->N--;

    }

    // v tem mais de uma aresta
    else{
        
        // Tenta selecionar uma aresta que não é de corte
        for (int i = 0; i < degrees[v]; i++){
            
            // Remove uma aresta de v
            w = pop_edge(g, v);

            // v-w não é uma aresta de corte
            if ( is_bridge(g, v, w) == 0 )
                break;
            
        }
        
        // Remove a aresta v -> w
        remove_edge(g, v, w);
        degrees[v]--;
        
    }

    // Remove a aresta w -> v
    remove_edge(g, w, v);
    degrees[w]--;

    printf(" %d", w);

    // Visita ao próximo vértice
    fleury_next_edge(g, w, degrees);

}

// Algoritmo de Fleury para cálculo de caminhos e ciclos eulerianos em grafos não direcionados
void fleury(Graph* g){

    // Graph* c = copy_graph(g);

    // Lista de graus dos vértices
    int* degrees = (int*) calloc( g->N, sizeof(int) );

    // Vértice inicial
    vertex start = 0;

    // Número de vértices de grau ímpar
    int n_odds = 0;
    
    // Calcula os graus dos vértices
    for (vertex v = 0; v < g->N; v++){
        
        // Calcula o grau do vértice v
        degrees[v] = degree(g, v);

        //
        if( degrees[v] % 2 != 0 ){
            n_odds++;
            start = v;
        }

        //
        else if ( n_odds == 0 && degrees[v] > 1 )
            start = v;
        
        //
        if( n_odds > 2)
            break;

    }

    // Verifica se grafo é Euleriano, Semi-Euleriano ou Não Euleriano
    if ( n_odds == 0 ){
        printf("\nGrafo Euleriano\n");
    }
    else if ( n_odds == 2 ){
        printf("\nGrafo Semi-Euleriano\n");
    }
    else{
        printf("\nGrafo Não Euleriano\n");
        return;
    }

    printf("Caminho: %d", start);

    // Chamada ao procedimento recursivo
    fleury_next_edge(g, start, degrees);

    printf("\n\n");
}

// Exemplo
int main(){

    Graph* g = new_graph(5);
    add_edge(g, 0, 1, 0, 0);
    add_edge(g, 1, 3, 0, 0);
    add_edge(g, 1, 2, 0, 0);
    add_edge(g, 2, 0, 0, 0);
    add_edge(g, 3, 4, 0, 0);
    add_edge(g, 4, 1, 0, 0);

    printf("Grafo não direcionado: \n");
    print_graph(g);

    fleury(g);

    return 0;
}
