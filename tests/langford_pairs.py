def langford_pairs(n):
    subsets = []
    for i in range(1, n + 1):
        for j in range(1, 2*n):
            k = i + j + 1
            assert k <= 2 * n
            subsets.append([2*n + i, j, k])
    return 3*n, 0, subsets