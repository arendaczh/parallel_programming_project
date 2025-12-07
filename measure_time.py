import sys
import time
import subprocess
import os


class Runner:
    def __init__(self):
        pass

    def compile(self, source: str, binary: str, flags=[]):
        print(f"Compiling {source}...")
        result = subprocess.run(
            ["g++", source, "-o", binary, *flags], capture_output=True, text=True
        )
        if result.returncode != 0:
            raise RuntimeError("Compilation failed:\n" + result.stderr)

    def run(
        self,
        binary: str,
        input_file: str,
        output_file: str,
        time_file: str | None,
        runs: int = 1,
    ):
        print(f"Running tests for {binary} from {input_file}...")
        os.makedirs(os.path.dirname(output_file), exist_ok=True)
        if time_file:
            os.makedirs(os.path.dirname(time_file), exist_ok=True)

        with open(input_file, "rb") as in_f:
            input_data = in_f.read()

        times = []
        with open(output_file, "wb") as out_f:
            start = time.perf_counter()  # performance counter
            p = subprocess.Popen(binary, stdin=subprocess.PIPE, stdout=out_f)
            p.communicate(input_data)
            end = time.perf_counter()
        times.append(end - start)

        for run in range(runs - 1):
            start = time.perf_counter()  # performance counter
            p = subprocess.Popen(
                binary, stdin=subprocess.PIPE, stdout=subprocess.DEVNULL
            )
            p.communicate(input_data)
            end = time.perf_counter()
            times.append(end - start)
        self.times = times

        mean = sum(times) / runs
        if time_file:
            with open(time_file, "w") as f:
                f.write(
                    "-------------------------- Time results --------------------------\n"
                )
                for t in self.times:
                    f.write(str(t) + " ")
                f.write(f"\nAvg time: {mean}\n")
        return mean
