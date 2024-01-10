import networkx as nx

def is_split_graph(graph):
    # Check if the graph is connected
    if not nx.is_connected(graph):
        return False

    # Check if the graph is a split graph
    for node in graph.nodes:
        neighbors = set(graph.neighbors(node))
        if neighbors.issubset(set(graph.nodes)) and not neighbors.isdisjoint(set(graph.nodes)):
            # Node and its neighbors form a clique
            independent_set = set(graph.nodes) - neighbors
            if not nx.is_independent_set(graph, independent_set):
                return False
    return True

# Example usage
G = nx.Graph()
G.add_edges_from([(1, 2), (2, 3), (3, 4), (4, 1), (5, 6)])

if is_split_graph(G):
    print("The graph is a split graph.")
else:
    print("The graph is not a split graph.")
