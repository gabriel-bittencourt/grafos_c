MAKEFLAGS += --no-print-directory

# Traversing and searching
bfs:
	@make _search file=BFS
dfs:
	@make _search file=DFS
_search:
	@make run folder=search file=$(file)

# Eulerian paths
hierholzer:
	@make _eulerian file=hierholzer
fleury:
	@make _eulerian file=fleury
_eulerian:
	@make run folder=eulerian file=$(file)

# Minimum spanning tree
kruskal:
	@make _mst file=kruskal
prim:
	@make _mst file=prim
_mst:
	@make run folder=mst file=$(file)

# Shortest paths
bellman-ford:
	@make _shortest_path file=bellman-ford
dijkstra:
	@make _shortest_path file=dijkstra
_shortest_path:
	@make run folder=shortest-path file=$(file)


run:
	@gcc $(folder)/$(file).c graph.c -o $(file).out


clean:
	@rm *.out
