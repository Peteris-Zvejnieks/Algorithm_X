from DancingLinks import DLX

class Algorithm_X(DLX):
    def __init__(self, primary_items: int, secondary_items: int = 0):
        super().__init__(primary_items, secondary_items)

    def __iter__(self):
        self.make_generator()
        return self