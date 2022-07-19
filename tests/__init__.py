import unittest
from Algorithm_X import Algorithm_X

from dags import leafy_majority_graphs
from langford_pairs import langford_pairs
from n_queens import n_queens_primary, n_queens_secondary


def n_solutions_for_a_problem(problem, complexity):
    primary_items, secondary_items, subsets = problem(complexity)
    algox = Algorithm_X(primary_items, secondary_items)
    for subset in subsets:
        algox.add_subset(subset)
    return len(algox)


class Test_Algorithm_X(unittest.TestCase):

    def test_problem(self, problem, n, n_answers):
        self.assertEqual(n_solutions_for_a_problem(problem, n), n_answers)

    def test_leafy_majority_graphs(self):
        problem = leafy_majority_graphs
        self.test_problem(problem, 4, 56)
        self.test_problem(problem, 5, 616)
        self.test_problem(problem, 6, 9856)
        self.test_problem(problem, 7, 216832)

    def test_langford_pairs(self):
        problem = langford_pairs
        self.test_problem(problem, 3, 2)
        self.test_problem(problem, 4, 2)
        self.test_problem(problem, 5, 0)
        self.test_problem(problem, 8, 300)
        self.test_problem(problem, 11, 35584)

    def test_n_queens_primary(self):
        problem = n_queens_primary
        self.test_problem(problem, 4, 2)
        self.test_problem(problem, 8, 92)
        self.test_problem(problem, 10, 724)

    def n_queens_secondary(self):
        problem = n_queens_secondary
        self.test_problem(problem, 4, 2)
        self.test_problem(problem, 8, 92)
        self.test_problem(problem, 10, 724)


if __name__ == '__main__':
    unittest.main()
