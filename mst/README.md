# Árvore geradora de custo mínimo (Minimum spanning tree - MST)

Uma **árvore geradora** é um subconjunto de arestas que forma uma árvore contendo todos os vértices do grafo.

Uma **árvore geradora de custo mínimo** é uma árvore geradora que tem o menor peso total possível em um grafo com arestas com pesos.

|Árvore geradora            | Árvore geradora de custo mínimo|
|:-------------------------:|:-------------------------:|
![](https://miro.medium.com/max/742/1*EnYcZx503uM9rrUKuF2-XQ.png) | ![](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d2/Minimum_spanning_tree.svg/595px-Minimum_spanning_tree.svg.png)

## Algoritmo de Kruskal

O algoritmo adiciona as arestas uma a uma na árvore geradora.
É um algoritmo guloso que a cada passo seleciona a aresta de menor peso e verifica se esta aresta cria ciclo (i.e. conecta dois vértices da mesma subárvore).
Se não, adiciona a aresta e conecta as subárvores.

Utilizando uma estrutura auxiliar de conjuntos disjuntos, o algoritmo tem complexidade O(m log n). (**m**: nº de arestas; **n**: nº de vértices)


## Algoritmo de Prim

O algoritmo inicializa a partir de um determinado vértice e, para cada etapa, seleciona o vértice com menor peso, que já está conectado ao vértice inicial na árvore gerada
(utilizando uma fila de prioridade).

A implementação do algoritmo utilizando um heap binário de mínimo para manter a fila de prioridade tem complexidade O(m log n). (**m**: nº de arestas; **n**: nº de vértices)

## Vizualização dos algoritmos

| Algoritm de Kruskal       | Algoritmo de Prim |
|:-------------------------:|:-------------------------:|
![Vizualização algoritmo de Kruskal](https://upload.wikimedia.org/wikipedia/commons/b/bb/KruskalDemo.gif) | ![Vizualização algoritmo de Prim](https://upload.wikimedia.org/wikipedia/commons/9/9b/PrimAlgDemo.gif)

### Referências
- [Árvore de extensão mínima - Wikipedia](https://pt.wikipedia.org/wiki/%C3%81rvore_de_extens%C3%A3o_m%C3%ADnima)
- [Algoritmo de Prim - Wikipedia](https://pt.wikipedia.org/wiki/Algoritmo_de_Prim)
- [Algoritmo de Kruskal - Wikipedia](https://pt.wikipedia.org/wiki/Algoritmo_de_Kruskal)
- [(EN) Minimum Spanning Tree - Medium](https://medium.com/@khushalijivani31/minimum-spanning-tree-8ba5cd583a93)
