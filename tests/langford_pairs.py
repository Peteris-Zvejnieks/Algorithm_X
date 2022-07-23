from DancingLinks import DLX

def langford_pairs(n):
    AlgoX = DLX(3*n)
    for i in range(1, n + 1):
        for j in range(1, 2*n - i):
            k = i + j + 1
            AlgoX.add_subset([2*n + i, j, k])
    return len(AlgoX)

def test_langford_pairs():
    assert langford_pairs(3) == 2
    assert langford_pairs(4) == 2
    assert langford_pairs(5) == 0
    assert langford_pairs(8) == 300
    assert langford_pairs(11) == 35584