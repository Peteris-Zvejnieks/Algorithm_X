from DancingLinks import DLX

def n_queens_primary(n):
    num_items = 6 * n - 2
    column_offset = n
    a_offset = 2 * n - 1
    b_offset = 5 * n - 1

    AlgoX = DLX(num_items)

    for i in range(1, n + 1):
        for j in range(1, n + 1):
            row = i
            col = column_offset + j
            a = a_offset + i + j
            b = b_offset + i - j
            AlgoX.add_subset([row, col, a, b])

    for i in range(2*n + 1, num_items + 1):
        AlgoX.add_subset([i])

    return len(AlgoX)

def test_n_queens_primary():
    assert n_queens_primary(4) == 2
    assert n_queens_primary(8) == 92
    assert n_queens_primary(10) == 724

def n_queens_secondary(n):
    primary_items = 2 * n
    secondary_items = 4 * n - 2
    column_offset = n
    a_offset = 2 * n - 1
    b_offset = 5 * n - 1

    dlx = DLX(primary_items, secondary_items)

    for i in range(1, n + 1):
        for j in range(1, n + 1):
            row = i
            col = column_offset + j
            a = a_offset + i + j
            b = b_offset + i - j
            dlx.add_subset([row, col, a, b])

    return len(dlx)

def test_n_queens_secondary():
    assert n_queens_secondary(4) == 2
    assert n_queens_secondary(8) == 92
    assert n_queens_secondary(10) == 724
