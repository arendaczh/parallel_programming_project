#!/bin/bash

# Check if an argument is provided
if [ $# -ne 1 ]; then
    echo "Usage: $0 <output_filename>"
    exit 1
fi

OUTPUT_FILE=$1

# Execute the Python command with the given output filename
python3 measure_time.py ./$OUTPUT_FILE in/1.in out/openmp/out/"$OUTPUT_FILE".out out/openmp/time/"$OUTPUT_FILE".out
python3 measure_time.py ./$OUTPUT_FILE in/1.in out/openmp/out/"$OUTPUT_FILE".out out/openmp/time/"$OUTPUT_FILE".out
python3 measure_time.py ./$OUTPUT_FILE in/1.in out/openmp/out/"$OUTPUT_FILE".out out/openmp/time/"$OUTPUT_FILE".out
python3 measure_time.py ./$OUTPUT_FILE in/1.in out/openmp/out/"$OUTPUT_FILE".out out/openmp/time/"$OUTPUT_FILE".out
