from generate_tests import TestGenerator
from measure_time import Runner
from run_tests import Executer
import os


def generate_tests(num: int):
    generator = TestGenerator(
        100, example_size=[20000, 100000], number_size=[1000, 10000000]
    )
    runner = Runner()
    runner.compile(source="ok.cpp", binary="ok")

    for i in range(1, num + 1):
        print(f"Generate tests: {i}/{num}")
        generator.generate(f"in/{i}.in")
        runner.run(
            binary="./ok",
            input_file=f"in/{i}.in",
            output_file=f"expected/{i}.out",
            time_file=None,
        )


def run_single_thread(file, binary):
    executer = Executer()

    print(f"Running test {file}")

    executer.singe_thread(file, binary)
    executer.compare_single_thread()


def run_open_mp(file, binary):
    executer = Executer()

    print(f"Running test {file}")

    executer.openmp(file, binary)
    executer.compare_openmp()


def run_threads(file, binary):
    executer = Executer()

    print(f"Running test {file}")

    executer.threads(file, binary)
    executer.compare_single_thread()


print("---------------- GENERATE TESTS ----------------")
generate_tests(5)
print("---------------- SINGLE THREAD ----------------")
run_single_thread("code/single_thread.cpp", "code/_single_thread")
# print("---------------- STD THREADS ----------------")
# run_threads("code/threads.cpp", "code/_threads")
# print("---------------- OPEN MP ----------------")
# run_open_mp("code/openmp.cpp", "code/_openmp")
