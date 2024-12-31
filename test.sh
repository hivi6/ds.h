#!/bin/sh

# Remove all the binaries
make clean || {
    echo "Something went wrong while running make clean";
    exit 1;
}

# Generate all the binaries
echo
make || {
    echo "Something went wrong while running make";
    exit 1;
}

# Run all the binaries and compare outputs
echo
total_test=0;
passed_test=0;
for bin in bin/*; do
    total_test=$((total_test + 1))
    bin_out=$bin.out;
    test_out=${bin_out/bin\//test\/};

    echo "TESTING $bin";

    ./$bin 2>&1 > $bin_out || {
	echo "- Something went wrong while running $bin";
	echo "- Last returned value was non-zero";
	echo "- check $bin.out";
	echo "- | FAILED |";
	continue;
    }

    diff $bin_out $test_out 2>&1 > /dev/null || {
	echo "- Something went wrong while comparing output files";
	echo "- check $bin_out";
	echo "- | FAILED |";
	continue;
    }

    echo "- | PASSED |";
    passed_test=$((passed_test + 1))
done

# Give test summary
echo;
echo "TEST SUMMARY:";
echo "TOTAL TESTS: $total_test | PASSED TESTS: $passed_test";

