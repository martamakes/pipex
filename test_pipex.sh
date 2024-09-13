#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Create output directories
mkdir -p output/expected output/actual

# Function to run a test
run_test() {
    test_name=$1
    command=$2
    expected_output=$3
    expected_exit_code=$4

    echo -n "Running test: $test_name ... "
    output=$(eval $command 2>&1)
    exit_code=$?

    echo "$expected_output" > "output/expected/$test_name"
    echo "$output" > "output/actual/$test_name"

    if diff -q "output/expected/$test_name" "output/actual/$test_name" >/dev/null && [ $exit_code -eq $expected_exit_code ]; then
        echo -e "${GREEN}PASSED${NC}"
    else
        echo -e "${RED}FAILED${NC}"
        echo "Differences:"
        diff -u "output/expected/$test_name" "output/actual/$test_name"
        echo "Expected exit code: $expected_exit_code"
        echo "Actual exit code: $exit_code"
    fi
}

# Compile the program
make re

# Create test input files
echo "Hello, World!" > infile
echo "This is a test file with multiple lines.
It has some content.
Let's count the words." > longtest.txt
echo "Hello! How are you?" > specialtest.txt

# Test 1: Incorrect number of arguments
run_test "incorrect_args" \
         "./pipex infile cmd1 outfile" \
         "Error: Invalid usage. Use: ./pipex file1 cmd1 cmd2 file2" \
         1

# Test 2: Empty argument
run_test "empty_arg" \
         "./pipex infile \"\" cmd2 outfile" \
         "Error: Empty arguments are not allowed" \
         1

# Test 3: Non-existent input file
run_test "nonexistent_input" \
         "./pipex nonexistent_file \"cat\" \"wc -l\" outfile" \
         "Error: Unable to open input file" \
         1

# Test 4: No permission to read input file
touch no_permission_file
chmod 000 no_permission_file
run_test "no_read_permission" \
         "./pipex no_permission_file \"cat\" \"wc -l\" outfile" \
         "Error: Permission denied for input file" \
         1
chmod 644 no_permission_file

# Test 5: No permission to write to output file
touch no_write_permission
chmod 444 no_write_permission
run_test "no_write_permission" \
         "./pipex infile \"cat\" \"wc -l\" no_write_permission" \
         "Error: Permission denied for output file" \
         1
chmod 644 no_write_permission

# Test 6: Invalid command
run_test "invalid_command" \
         "./pipex infile \"invalid_command\" \"wc -l\" outfile" \
         "Error: Command not found: invalid_command" \
         127

# Test 7: Valid usage
run_test "valid_usage" \
         "./pipex infile \"cat\" \"wc -l\" outfile" \
         "" \
         0
echo "       1" > output/expected/valid_usage_outfile
cp outfile output/actual/valid_usage_outfile
diff -u output/expected/valid_usage_outfile output/actual/valid_usage_outfile

# Test 8: Long command
run_test "long_command" \
         "./pipex longtest.txt \"cat\" \"tr ' ' '\n' | sort | uniq -c | sort -nr | head -n 3\" outfile" \
         "" \
         0
< longtest.txt cat | tr ' ' '\n' | sort | uniq -c | sort -nr | head -n 3 > output/expected/long_command_outfile
cp outfile output/actual/long_command_outfile
diff -u output/expected/long_command_outfile output/actual/long_command_outfile

# Test 9: Command with special characters
run_test "special_characters" \
         "./pipex specialtest.txt \"grep 'How are'\" \"sed 's/How/Where/'\" outfile" \
         "" \
         0
echo "Where are you?" > output/expected/special_characters_outfile
cp outfile output/actual/special_characters_outfile
diff -u output/expected/special_characters_outfile output/actual/special_characters_outfile

# Test 10: Very long input file
yes "This is a test line." | head -n 1000 > verylongfile.txt
run_test "very_long_input" \
         "./pipex verylongfile.txt \"cat\" \"wc -l\" outfile" \
         "" \
         0
echo "    1000" > output/expected/very_long_input_outfile
cp outfile output/actual/very_long_input_outfile
diff -u output/expected/very_long_input_outfile output/actual/very_long_input_outfile

# Test 11: Command not found in PATH
OLD_PATH=$PATH
export PATH=""
run_test "command_not_in_path" \
         "./pipex infile \"ls\" \"wc -l\" outfile" \
         "Error: Command not found: ls" \
         127
export PATH=$OLD_PATH

# Test 12: Input file is a directory
mkdir testdir
run_test "input_is_directory" \
         "./pipex testdir \"cat\" \"wc -l\" outfile" \
         "Error: Input file is a directory" \
         1
rmdir testdir

# Test 13: Output file is a directory
mkdir outdir
run_test "output_is_directory" \
         "./pipex infile \"cat\" \"wc -l\" outdir" \
         "Error: Output file is a directory" \
         1
rmdir outdir

# Memory leak test
if command -v valgrind &> /dev/null; then
    echo "Running memory leak test..."
    valgrind --leak-check=full --error-exitcode=1 ./pipex infile "cat" "wc -l" outfile > output/valgrind_output 2>&1
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}No memory leaks detected${NC}"
    else
        echo -e "${RED}Memory leaks detected${NC}"
        cat output/valgrind_output
    fi
else
    echo "Valgrind not installed, skipping memory leak test"
fi

# Clean up
make fclean