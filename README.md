
Biblioteca em C com estrutura de grafos em representação com listas de adjacências e alguns algoritmos populares.

### Estrutura
A estrutura do grafo pode ser encontrada em [graph.h](graph.h).

### Algoritmos
* **[Busca e travessia](search)**
  * Busca em profundidade (DFS) 
  * Busca em largura (BFS)
* **[Árvores geradoras de custo mínimo](mst)**
  * Kruskal
  * Prim
* **[Caminhos de custo mínimo a partir de um vértice](shortest-path)**
  * Dijkstra
  * Bellman-Ford
* **[Caminhos e ciclos eulerianos](eulerian)**
  * Hierholzer
  * Fleury


### Execução

É necessário compilar o arquivo [graph.c](graph.c) para a execução dos demais algoritmos.<br/>
Os algoritmos podem ser executados por comandos do makefile em um ambiente linux.

Exemplo em um ambiente linux:

```sh
# Gera um executável
$ make dijkstra

# Executa
$ ./dijkstra.out
```
