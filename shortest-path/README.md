# Caminhos de custo mínimo (Shortest paths)

Um **caminho de custo mínimo** é um subconjunto de arestas que forma um caminho de menor peso possível entre dois vértices no grafo.

| ![](https://miro.medium.com/max/600/1*OUqMXd2jmLprCqWULLll8w.gif) |
| :---------------------------------------------------------------: |
| Caminho de menor custo entre os vértices 1 e 6 |


# Problema dos caminhos de custo mínimo a partir de um vértice (Single-source shortest path problem)

Consiste em encontrar os caminhos de custo mínimo entre um determinado vértice e todos os outros vértices do grafo.

## Algoritmo de Dijkstra

Calcula os caminhos de custo mínimo em um grafo com arestas de pesos não negativos.

O algoritmo procede da seguinte forma:

  - Define-se um conjunto que mantém os custos totais para se alcançar cada vértice, onde todos vértices recebem um custo "infinito",
    exceto o vértice inicial, que recebe custo 0 (zero).
  - Em cada etapa, seleciona o atual vértice que tem menor custo total e percorre-se todas as arestas a partir dele.
  - Para cada aresta analisada, realiza-se o **relaxamento** da aresta, isto é:
    - Suponha que estamos verificando a aresta *uv*;
    - Sejam **p** o peso da aresta, **pu** o custo atual em *u* e **pv** o custo atual em *v*;
    - Verificamos se **p + pu < pv**, ou seja, se a aresta diminui o custo total atual em *v*;
    - Se sim, adicionamos a aresta ao caminho e atualizamos o custo total em *v*;
 
Ao final da execução, teremos os caminhos de custos mínimos e os respectivos custos entre o vértice inicial e todos os outros vértices do grafo.
Os vértices que não podem ser alcançados a partir do vértice inicial terão custo infinito.

A complexidade depende da estrutura que será utilizada para manter os custos dos vértices.
No [código acima](shortest-path/dijkstra.c), o algoritmo foi implementado utilizando um heap binário, e portanto, tem complexidade O(m log n) (**m**: nº de arestas; **n**: nº de vértices).

| ![](https://steemitimages.com/0x0/https://i.imgur.com/dWtprX5.gif) |
| :---------------------------------------------------------------: |
| Execução do algoritmo de Dijkstra |


## Algoritmo de Bellman-Ford

Calcula os caminhos de custo mínimo em um grafo com aresta com peso.

Descrição do algoritmo:

  - Define-se um conjunto que mantém os custos totais para se alcançar cada vértice, onde todos vértices recebem um custo "infinito",
    exceto o vértice inicial, que recebe custo 0 (zero).
  - Realiza-se seguinte procedimento **|V|-1** vezes (onde **|V|** é o número de vértices do grafo).
    - Percorre-se todas as arestas do grafo e realiza-se o relaxamento (descrito anteriormente) em cada uma delas.
 
Uma prova da corretude do algoritmo pode sem verificada (em inglês) [aqui](https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm#Proof_of_correctness).

A complexidade do algoritmo é O(n*m) (**m**: nº de arestas; **n**: nº de vértices).

| ![](https://miro.medium.com/max/840/1*1uN5vzAA0PvZVND8fu5iig.gif) |
| :---------------------------------------------------------------: |
| Execução do algoritmo de Bellman-Ford |

### Referências
- [Problema do caminho mínimo - Wikipedia](https://pt.wikipedia.org/wiki/Problema_do_caminho_m%C3%ADnimo)
- [Algoritmo de Dijkstra - Wikipedia](https://pt.wikipedia.org/wiki/Algoritmo_de_Dijkstra)
- [Algoritmo de Bellman-Ford - Wikipedia](https://pt.wikipedia.org/wiki/Algoritmo_de_Bellman-Ford)
- [(EN) 10 Graph Algorithms Visually Explained - Medium](https://towardsdatascience.com/10-graph-algorithms-visually-explained-e57faa1336f3)
