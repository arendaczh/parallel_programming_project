#!/usr/bin/env bash

# Usage: ./generate.sh output_file test_number min_example max_example min_number max_number
# Example: ./generate.sh out.txt 5 2 100 10 1000

OUT="$1"
TESTS="$2"
MIN_EX="$3"
MAX_EX="$4"
MIN_NUM="$5"
MAX_NUM="$6"

# Write the number of tests first
echo "$TESTS" > "$OUT"

for ((t=0; t<TESTS; t++)); do
    # Random n and k
    n=$((RANDOM % (MAX_EX - MIN_EX + 1) + MIN_EX))
    k=$((RANDOM % (MAX_NUM - MIN_NUM + 1) + MIN_NUM))
    echo "$n $k" >> "$OUT"

    # Generate n random numbers for this test
    for ((i=0; i<n; i++)); do
        num=$((RANDOM % (MAX_NUM - MIN_NUM + 1) + MIN_NUM))
        echo -n "$num " >> "$OUT"
    done
    echo "" >> "$OUT"
done
