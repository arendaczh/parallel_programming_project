from random import randint
from typing import List
import sys

class TestGenerator:
    def __init__(
        self,
        test_number: int,
        example_size: List = [2, 20000],
        number_size=[100, 100000000],
    ):
        self.test_number = test_number
        self.example_size = example_size
        self.number_size = number_size

    def generate(self, out_path: str):
        with open(out_path, "w") as out:
            z = self.test_number
            out.write(str(z) + "\n")

            for _ in range(z):
                n = randint(self.example_size[0], self.example_size[-1])
                k = randint(0, self.number_size[0])
                out.write(str(n) + " " + str(k) + "\n")
                for i in range(n):
                    number = randint(self.number_size[0], self.number_size[-1])
                    out.write(str(number) + " ")
                out.write('\n')
