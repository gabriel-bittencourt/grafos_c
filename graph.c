#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "./graph.h"


// Cria um grafo de N vértices
Graph* new_graph(int N){

    // Cria um novo grafo
    Graph* new = (Graph*) malloc(sizeof(Graph));
    new->N = N;

    // Cria um vetor de tamanho N de Listas de Adjacências
    new->adj = (AdjList*) malloc(N * sizeof(AdjList));

    // Inicializa cada elemento da lista
    for (int i = 0; i < N; i++) {
        new->adj[i].head = NULL;
    }
    
    return new;
}

// Cria um novo nó na lista
Node* new_node(vertex dest, int weight){
    
    Node* new = (Node*) malloc(sizeof(Node));
    new->dest = dest;
    new->weight = weight;
    new->next = NULL;

    return new;
}

// Cria uma nova aresta em um grafo direcionado
// Adiciona uma aresta de v para w
void add_edge_directed(Graph* g, vertex v, vertex w, int weight){
    
    // Cria um nó w e insere no início da lista de adjacências de v
    Node* newNode = new_node(w, weight);
    newNode->next = g->adj[v].head;
    g->adj[v].head = newNode;

}

// Adiciona uma aresta no grafo
// O parâmetro directed indica se a aresta é direcionada ou não
// Se directed == 0 -> Insere não direcionado
// Caso contrário   -> Insere direcionado
void add_edge(Graph* g, vertex v, vertex w, int weight, int directed){
    
    //
    g->M++;

    // Adiciona uma aresta de v para w
    add_edge_directed(g, v, w, weight);

    // Adiciona uma aresta de w para v, dependendo do parâmetro
    if( !directed )
        add_edge_directed(g, w, v, weight);

}

// Remove uma aresta do grafo (Apenas no sentido v -> w)
void remove_edge(Graph* g, vertex v, vertex w){

    // Auxiliares
    Node* prev = NULL;
    Node* curr = g->adj[v].head;
    
    // Percorre a lista de adjacências
    while(curr && curr->dest != w){
        prev = curr;
        curr = curr->next;
    }

    // Não existe aresta
    if( !curr )
        return;

    // Se elemento era o primeiro da lista, o segundo elemento torna-se o novo head
    if( !prev )
        g->adj[v].head = curr->next;

    // O elemento anterior se liga ao próximo do atual
    else
        prev->next = curr->next;

    // Libera a memória
    free(curr);

}

// Remove a última aresta da lista de adjacências de v e retorna o valor removido
vertex pop_edge(Graph* g, vertex v){

    // Auxiliares
    Node* prev = NULL;
    Node* curr = g->adj[v].head;

    // Não existe nenhuma aresta a partir de v
    if( !curr )
        return -1;

    // Percorre todas as arestas de v
    while ( curr->next ){
        prev = curr;
        curr = curr->next;
    }
    
    // Se v só tinha uma aresta, NULL é o novo head
    if( !prev )
        g->adj[v].head = NULL;

    // Penúltima aresta de v aponta para NULL
    else
        prev->next = NULL;

    // Salva o valor da última aresta
    vertex w = curr->dest;

    // Libera a memória
    free(curr);

    return w;
}

// Remove a primeira aresta da lista de adjacências de v e retorna o valor removido
vertex delete_edge(Graph* g, vertex v){

    // head atual
    Node* head = g->adj[v].head;

    // Não existe nenhuma aresta a partir de v
    if( !head )
        return -1;

    // Segundo elemento (ou NULL se não houver) é o novo head
    g->adj[v].head = head->next;

    // Salva o valor da última aresta
    vertex w = head->dest;

    // Libera a memória
    free(head);

    return w;
}

// Copia um grafo
Graph* copy_graph(Graph* g){
    
    // Cria um novo grafo de mesmo tamanho
    Graph* new = new_graph(g->N);

    // Para cada vértice de g
    for (int v = 0; v < g->N; v++){
        
        // Para cada aresta de v
        for ( Node* w = g->adj[v].head; w; w = w->next ){
            // Insere a aresta no novo grafo
            add_edge(new, v, w->dest, w->weight, 1);
        }
    }
    
    return new;
}

// Imprime uma lista de adjacências recursivamente
void print_list(Node* node){
    if( node ){
        if (node->weight)
            printf(" -> (%-2d|%2d)", node->dest, node->weight);
        else
            printf(" -> %d", node->dest);
        print_list(node->next);
    }
}

// Retorna o grau de um vértice
int degree(Graph*g, vertex v){
    
    int c = 0;

    Node* aux = g->adj[v].head;
    while( aux ){
        c++;
        aux = aux->next;
    }

    return c;
}

// Imprime as listas de adjacências de um grafo
void print_graph(Graph* g){

    for (int v = 0; v < g->N; v++){

        printf("| %d |", v);
        print_list(g->adj[v].head);
        printf("\n");
    }

}

// Algoritmo DFS modificado para contar número de vértices alcançados a partir de v
void DFS_count(Graph* g, vertex v, int* counter, int* visited){

    // Marca v
    visited[v] = 1;

    // Incrementa o contador
    (*counter)++;

    // Para cada vértice w adjacente a v
    for (
        Node* w = g->adj[v].head;
        w;
        w = w->next
    ){
        // Se w não é marcado
        if( visited[w->dest] == 0 )
            DFS_count(g, w->dest, counter, visited);
    }

}

// Verifica se a aresta v->w é uma aresta de corte (em um grafo não direcionado)
// Retorna 1 se for aresta de corte
// Retorna 0 se não for aresta de corte
int is_bridge(Graph* g, vertex v, vertex w){

    // Remove a aresta v-w
    remove_edge(g, v, w);
    remove_edge(g, w, v);

    // Contador de vértices alcançados
    int counter = 0;

    // Vetor de visitados para algoritmo de DFS
    int* visited = (int*) calloc( g->N, sizeof(int) );

    // Cálculo do número de vértices alcançados por w
    DFS_count(g, w, &counter, visited);

    // Coloca as arestas de volta
    add_edge(g, v, w, 0, 0);

    // Se o número de vértices alcançados é menor que o número de vértices do grafo, então é aresta de corte
    if( counter < g->N )
        return 1;

    // Caso contrário, não é aresta de corte
    else
        return 0;

}

// Imprime para cada vértice o seu caminho de peso mínimo
void print_paths(Graph* g, int* dist, int* parent){
    for (vertex v = 0; v < g->N; v++){

        printf("Vértice %3d | Peso:", v);

        if ( dist[v] < INT_MAX )
            printf(" %3d |", dist[v]);
        else
            printf("   ∞ |");

        printf("Caminho: %d", v);

        vertex p = parent[v];
        while( p != -1 ){
            printf(" <- %d", p);
            p = parent[p];
        }
        printf("\n");
    }
    printf("\n");
}
