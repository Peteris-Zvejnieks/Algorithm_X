def leafy_majority_graphs(n: int):
    subsets = []
    secondary_items = ( n * ( n - 1 ) ) /
    offset = n
    for i in range(1, n + 1):
        subsets.append([i])
        for j in range(1, i):
            subsets.append([i, offset + j])
            for k in range(j + 1, i):
                subsets.append([i, offset + j, offset + k])
        offset += i - 1
    return n, secondary_items, subsets
