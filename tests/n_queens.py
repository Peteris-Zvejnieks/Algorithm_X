def n_queens_primary(n):
    num_items = 6 * n - 2
    column_offset = n
    a_offset = 2 * n - 1
    b_offset = 5 * n - 1

    subsets = []

    for i in range(1, n + 1):
        for j in range(1, n + 1):
            row = i
            col = column_offset + j
            a = a_offset + i + j
            b = b_offset + i - j
            subsets.append([row, col, a, b])

    for i in range(2*n + 1, num_items + 1):
        subsets.append([i])

    return secondary_items, 0, subsets


def n_queens_secondary(n):
    primary_items = 2 * n
    secondary_items = 4 * n - 2
    column_offset = n
    a_offset = 2 * n - 1
    b_offset = 5 * n - 1

    subsets = []

    for i in range(1, n + 1):
        for j in range(1, n + 1):
            row = i
            col = column_offset + j
            a = a_offset + i + j
            b = b_offset + i - j
            subsets.append([row, col, a, b])

    return primary_items, secondary_items, subsets
