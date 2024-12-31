#!/bin/sh
shopt -s extglob

# Generate all the binaries
make || {
    echo "Something went wrong while running make";
    exit 1;
}

# Run all the binaries and save the output
for bin in bin/!(*.out); do
    ./$bin > ./$bin.out;
done

# Compare all runtime output with provided output
for test_out in test/*.out; do
    bin_out=${test_out/test\//bin\/}
    passed=1
    diff $test_out $bin_out 2>&1 > /dev/null || {
	passed=0
    }
    passed_msg="| PASSED |";
    if [ $passed == 0 ]; then
	passed_msg="| FAILED |";
    fi
    echo "$passed_msg diff $test_out $bin_out"
done

# Remove all the binaries
make clean || {
    echo "Something went wrong while running make clean";
    exit 1;
}
