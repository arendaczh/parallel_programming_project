from measure_time import Runner
import os
import sys
import statistics

IN = "in"
EXPECTED = "expected"

SINGLE_THREAD_OUT = "out/single-thread/out"
SINGLE_THREAD_TIME = "out/single-thread/time"

THREADS_OUT = "out/threads/out"
THREADS_TIME = "out/threads/time"

OPENMP_OUT = "out/openmp/out"
OPENMP_TIME = "out/openmp/time"


class Executer:
    def __init__(self):
        self.runner = Runner()

    def _run(self, source, binary, tests, out, time, flags=[]):
        os.makedirs(out, exist_ok=True)
        os.makedirs(time, exist_ok=True)
        self.runner.compile(source=source, binary=binary, flags=flags)

        scores = []
        for filename in os.listdir(tests):
            input_path = os.path.join(tests, filename)

            if not os.path.isfile(input_path):
                continue

            name = os.path.splitext(filename)[0] + ".out"
            output_path = os.path.join(out, name)
            time_path = os.path.join(time, name)

            time_score = self.runner.run(
                    binary=binary,
                    input_file=input_path,
                    output_file=output_path,
                    time_file=time_path,
                    runs=1,
                )
            scores.append(time_score)
            # print(self.runner.mean_time(time_path))
        print(f"AVG TIME ACROSS ALL TESTS: {statistics.mean(scores)}")

    def singe_thread(self, source, binary):
        self._run(
            source=source,
            binary=binary,
            tests=IN,
            out=SINGLE_THREAD_OUT,
            time=SINGLE_THREAD_TIME,
            flags=[
                "-std=c++23",
                "-O2",
                "-Wall",
            ],
        )

    def threads(self, source, binary):
        self._run(
            source=source,
            binary=binary,
            tests=IN,
            out=THREADS_OUT,
            time=THREADS_TIME,
            flags=[
                "-std=c++23",
                "-O3",
                "-pthread",
                "-Wall"
            ],
        )

    def openmp(self, source, binary):
        self._run(
            source=source,
            binary=binary,
            tests=IN,
            out=OPENMP_OUT,
            time=OPENMP_TIME,
            flags=[
                "-std=c++23",
                "-O3",
                "-fopenmp",
                "-Wall"
            ],
        )

    def _compare(self, expected, result):
        os.makedirs(expected, exist_ok=True)
        os.makedirs(result, exist_ok=True)

        expected_files = sorted([f for f in os.listdir(expected)])
        result_file = sorted([f for f in os.listdir(result)])

        all_match = True
        for filename in expected_files:
            expected_path = os.path.join(expected, filename)
            result_path = os.path.join(result, filename)

            with open(expected_path, "r") as exp, open(result_path, "r") as res:
                expected_content = " ".join(exp.read().split())
                result_content = " ".join(res.read().split())

                if expected_content != result_content:
                    print(f"Files differ: {filename}")
                    all_match = False
        return all_match

    def compare_single_thread(self):
        res = self._compare(EXPECTED, SINGLE_THREAD_OUT)
        if res:
            print("SINGLE THREAD: ALL TESTS PASSED")

    def compare_threads(self):
        res = self._compare(EXPECTED, THREADS_OUT)
        if res:
            print("THREADS: ALL TESTS PASSED")

    def compare_openmp(self):
        res = self._compare(EXPECTED, OPENMP_OUT)
        if res:
            print("OPENMP: ALL TESTS PASSED")

