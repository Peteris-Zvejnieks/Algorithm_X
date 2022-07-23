from DancingLinks import DLX

def leafy_majority_graphs(n: int):
    secondary_items = (n * (n - 1)) // 2
    dlx = DLX(n, secondary_items)

    offset = n
    for i in range(1, n + 1):
        dlx.add_subset([i])
        for j in range(1, i):
            dlx.add_subset([i, offset + j])
            for k in range(j + 1, i):
                dlx.add_subset([i, offset + j, offset + k])
        offset += i - 1
    return len(dlx)

def test_leafy_majority_graphs():
    assert leafy_majority_graphs(4) == 56
    assert leafy_majority_graphs(5) == 616
    assert leafy_majority_graphs(6) == 9856
    assert leafy_majority_graphs(7) == 216832
