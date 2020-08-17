#ifndef _GRAPH_H
#define _GRAPH_H

// Definição das estruturas de dados

#define vertex int

// Elemento da lista de adjacências
typedef struct node Node;
struct node {
    vertex dest;  // Informação do vértice
    int weight;   // Peso da aresta
    Node* next;   // Ponteiro para o próximo elemento da lista de adjacências
};

// Lista de adjacências
typedef struct adjList AdjList;
struct adjList {
    Node* head;      // Ponteiro para o primeiro elemento da lista de adjacências
};

// Estrutura do grafo
typedef struct graph Graph;
struct graph {
    int N;           // Número de vértices
    int M;           // Número de arestas
    AdjList* adj;    // Vetor de listas de adjacências
};

// A estrutura do dígrafo é igual a estrutura do grafo não orientado
typedef Graph Digraph;


/*     Métodos básicos     */

// Cria um grafo de N vértices
Graph* new_graph(int N);

// Cria um novo nó na lista
Node* new_node(vertex dest, int weight);

// Adiciona uma aresta no grafo
// O parâmetro directed indica se a aresta é direcionada ou não
// Se directed == 0  -> Insere não direcionado
// Caso contrário    -> Insere direcionado
void add_edge(Graph* g, vertex v, vertex w, int weight, int directed);

// Cria uma nova aresta em um grafo direcionado
// Adiciona uma aresta de v para w
void add_edge_directed(Graph* g, vertex v, vertex w, int weight);

// Remove uma aresta do grafo (Apenas no sentido v -> w)
void remove_edge(Graph* g, vertex v, vertex w);

// Remove a última aresta da lista de adjacências de v e retorna o valor removido
vertex pop_edge(Graph* g, vertex v);

// Remove a primeira aresta da lista de adjacências de v e retorna o valor removido
vertex delete_edge(Graph* g, vertex v);

// Copia um grafo
Graph* copy_graph(Graph* g);

// Imprime uma lista de adjacências recursivamente
void print_list(Node* node);

// Retorna o grau de um vértice
int degree(Graph*g, vertex v);

// Imprime as listas de adjacências de um grafo
void print_graph(Graph* g);

// Verifica se a aresta v->w é uma aresta de corte (em um grafo não direcionado)
// Retorna 1 se for aresta de corte
// Retorna 0 se não for aresta de corte
int is_bridge(Graph* g, vertex v, vertex w);

// Algoritmo DFS modificado para contar número de vértices alcançados a partir de v
void DFS_count(Graph* g, vertex v, int* counter, int* visited);

// Imprime para cada vértice o seu caminho de peso mínimo
void print_paths(Graph* g, int* dist, int* parent);

#endif
