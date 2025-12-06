import sys
import time
import subprocess


class Runner:
    def __init__(self, binary: str, input_file: str, output_file: str, runs: int = 1):
        self.binary = binary
        self.input_file = input_file
        self.output_file = output_file
        self.runs = runs

    def run(self):
        with open(self.input_file, "rb") as in_f:
            input_data = in_f.read()

        times = []
        with open(self.output_file, "wb") as out_f:
            start = time.perf_counter()  # performance counter
            p = subprocess.Popen(self.binary, stdin=subprocess.PIPE, stdout=out_f)
            p.communicate(input_data)
            end = time.perf_counter()
        times.append(end - start)

        for run in range(self.runs - 1):
            start = time.perf_counter()  # performance counter
            p = subprocess.Popen(
                self.binary, stdin=subprocess.PIPE, stdout=subprocess.DEVNULL
            )
            p.communicate(input_data)
            end = time.perf_counter()
            times.append(end - start)
        self.times = times
        return times

    def mean_time(self, out):
        mean = sum(self.times) / self.runs
        with open(out, "w") as f:
            f.write(
                "-------------------------- Time results --------------------------\n"
            )
            for time in self.times:
                f.write(str(time) + " ")
            f.write(f"\nAvg time: {mean}\n")
        return mean


if len(sys.argv) < 4:
    print("Provide arguments: <binary>, <input_file> <output_file> <time_file>")
    raise ValueError

binary = sys.argv[1]
input_file = sys.argv[2]
output_file = sys.argv[3]
time_file = sys.argv[4]

runner = Runner(binary, input_file, output_file, runs=1)
runner.run()
print(runner.mean_time(time_file))
