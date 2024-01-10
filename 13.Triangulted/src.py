# https://stackoverflow.com/questions/12367801/finding-all-cycles-in-undirected-graphs

#graph = [[0, 1], [0, 4], [1, 3], [1, 2], [2, 3], [3, 4], [1, 0], [4, 0], [3, 1], [2, 1], [3, 2], [4, 3]]
# graph = [[0, 3], [0, 4], [0, 5], [1, 4], [1, 5], [2, 3], [2, 4], [2, 5], [3, 0], [4, 0], [5, 0], [4, 1], [5, 1], [3, 2], [4, 2], [5, 2]]
#graph = [[0, 1], [0, 4], [1, 2], [1, 4], [1, 5], [2, 3], [2, 5], [2, 6], [3, 6], [4, 5], [5, 6], [1, 0], [4, 0], [2, 1], [4, 1], [5, 1], [3, 2], [5, 2], [6, 2], [6, 3], [5, 4], [6, 5]]

cycles = []

flag = True

def main():
    global graph
    global cycles
    for edge in graph:
        for node in edge:
            findNewCycles([node])
    for cy in cycles:
        path = [str(node) for node in cy]
        s = ",".join(path)
        # print(s)
        has_chord = hasChord(cy)
        print(f"{s} {'(Chord)' if has_chord else ''}")

    if flag is True:
        print("\n Triangulated Graph.\n")
    else:
        print("\n Not a Triangulated Graph.\n")

def findNewCycles(path):
    start_node = path[0]
    next_node= None
    sub = []

    #visit each edge and each node of each edge
    for edge in graph:
        node1, node2 = edge
        if start_node in edge:
                if node1 == start_node:
                    next_node = node2
                else:
                    next_node = node1
                if not visited(next_node, path):
                        # neighbor node not on path yet
                        sub = [next_node]
                        sub.extend(path)
                        # explore extended path
                        findNewCycles(sub)
                elif len(path) > 2  and next_node == path[-1]:
                        # cycle found
                        p = rotate_to_smallest(path)
                        inv = invert(p)
                        if isNew(p) and isNew(inv):
                            cycles.append(p)

def invert(path):
    return rotate_to_smallest(path[::-1])

#  rotate cycle path such that it begins with the smallest node
def rotate_to_smallest(path):
    n = path.index(min(path))
    return path[n:]+path[:n]

def isNew(path):
    return not path in cycles

def visited(node, path):
    return node in path

# Program to cyclically rotate an array by one
def cyclicRotate(input):
    # print(input[1:] + [input[0]])
    return(input[1:] + [input[0]])

def hasChord(cycle):
    global flag
    n = len(cycle)

    if n <= 3:
        return True  # Chord found

    cyc = cycle
    for k in range(n):
        for i in range(n):
            for j in range(i + 2, n-1):
                # print(cyc[i], cyc[j])
                if [cyc[i], cyc[j]] in graph and [cyc[j], cyc[i]] in graph:
                    return True  # Chord found
        cyc = cyclicRotate(cyc)
    flag = False
    return False  # No chord found

main()