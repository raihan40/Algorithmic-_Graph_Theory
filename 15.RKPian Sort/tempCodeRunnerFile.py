from collections import defaultdict, deque

def construct_graph(nums):
    graph = defaultdict(list)
    for i in range(len(nums)):
        for j in range(i + 1, len(nums)):
            if nums[j] > nums[i]:
                graph[i].append(j)
    return graph

def topological_sort(graph, nums):
    indegree = defaultdict(int)
    for node in graph:
        for neighbor in graph[node]:
            indegree[neighbor] += 1

    result = []
    queue = deque([node for node in graph if indegree[node] == 0])

    while queue:
        current = max(queue)
        queue.remove(current)
        result.append(nums[current])

        for neighbor in graph[current]:
            indegree[neighbor] -= 1
            if indegree[neighbor] == 0:
                queue.append(neighbor)

    return result

def main():
    nums = [16, 4, 10, 9, 53, 68, 73, 7, 2]
    graph = construct_graph(nums)
   # print(graph)
    result = topological_sort(graph, nums)

    print("Topological Order:")
    for node in result:
        print(node)

if __name__ == "__main__":
    main()
