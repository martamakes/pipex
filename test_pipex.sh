#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Function to run a test
run_test() {
    test_name=$1
    command=$2
    expected_output=$3
    expected_exit_code=$4

    echo -n "Running test: $test_name ... "
    output=$(eval $command 2>&1)
    exit_code=$?

    if [[ "$output" == "$expected_output" && $exit_code -eq $expected_exit_code ]]; then
        echo -e "${GREEN}PASSED${NC}"
    else
        echo -e "${RED}FAILED${NC}"
        echo "Expected output: $expected_output"
        echo "Actual output: $output"
        echo "Expected exit code: $expected_exit_code"
        echo "Actual exit code: $exit_code"
    fi
}

# Compile the program
make re

# Test 1: Incorrect number of arguments
run_test "Incorrect number of arguments" \
         "./pipex infile cmd1 outfile" \
         "Error: Invalid usage. Use: ./pipex file1 cmd1 cmd2 file2" \
         1

# Test 2: Empty argument
run_test "Empty argument" \
         "./pipex infile \"\" cmd2 outfile" \
         "Error: Empty arguments are not allowed" \
         1

# Test 3: Non-existent input file
run_test "Non-existent input file" \
         "./pipex nonexistent_file \"cat\" \"wc -l\" outfile" \
         "Error: Unable to open input file" \
         1

# Test 4: No permission to read input file
touch no_permission_file
chmod 000 no_permission_file
run_test "No permission to read input file" \
         "./pipex no_permission_file \"cat\" \"wc -l\" outfile" \
         "Error: Permission denied for input file" \
         1
chmod 644 no_permission_file
rm no_permission_file

# Test 5: No permission to write to output file
touch no_write_permission
chmod 444 no_write_permission
run_test "No permission to write to output file" \
         "./pipex infile \"cat\" \"wc -l\" no_write_permission" \
         "Error: Permission denied for output file" \
         1
chmod 644 no_write_permission
rm no_write_permission

# Test 6: Invalid command
run_test "Invalid command" \
         "./pipex infile \"invalid_command\" \"wc -l\" outfile" \
         "Error: Command not found: invalid_command" \
         127

# Test 7: Valid usage
echo "Hello, World!" > testfile
run_test "Valid usage" \
         "./pipex testfile \"cat\" \"wc -l\" outfile" \
         "" \
         0
if [ -f outfile ] && [ "$(cat outfile)" = "       1" ]; then
    echo -e "${GREEN}Output file content is correct${NC}"
else
    echo -e "${RED}Output file content is incorrect${NC}"
fi
rm testfile outfile

# Test 8: Long command
echo "This is a test file with multiple lines.\nIt has some content.\nLet's count the words." > longtest.txt
run_test "Long command" \
         "./pipex longtest.txt \"cat\" \"tr ' ' '\n' | sort | uniq -c | sort -nr | head -n 3\" outfile" \
         "" \
         0
if [ -f outfile ] && [ "$(cat outfile | wc -l)" = "3" ]; then
    echo -e "${GREEN}Long command output is correct${NC}"
else
    echo -e "${RED}Long command output is incorrect${NC}"
fi
rm longtest.txt outfile

# Test 9: Command with special characters
echo "Hello! How are you?" > specialtest.txt
run_test "Command with special characters" \
         "./pipex specialtest.txt \"grep 'How are'" "sed 's/How/Where/'\" outfile" \
         "" \
         0
if [ -f outfile ] && [ "$(cat outfile)" = "Where are you?" ]; then
    echo -e "${GREEN}Special characters handled correctly${NC}"
else
    echo -e "${RED}Special characters not handled correctly${NC}"
fi
rm specialtest.txt outfile

# # Test 10: Very long input file
# yes "This is a test line." | head -n 5 > verylongfile.txt
# run_test "Very long input file" \
#          "./pipex verylongfile.txt \"cat\" \"wc -l\" outfile" \
#          "" \
#          0
# if [ -f outfile ] && [ "$(cat outfile)" = "   5" ]; then
#     echo -e "${GREEN}Very long input file handled correctly${NC}"
# else
#     echo -e "${RED}Very long input file not handled correctly${NC}"
# fi
# rm verylongfile.txt outfile

# Test 11: Command not found in PATH
export PATH=""
run_test "Command not found in PATH" \
         "./pipex infile \"ls\" \"wc -l\" outfile" \
         "Error: Command not found: ls" \
         127
export PATH="$OLDPATH"

# Test 12: Input file is a directory
mkdir testdir
run_test "Input file is a directory" \
         "./pipex testdir \"cat\" \"wc -l\" outfile" \
         "Error: Input file is a directory" \
         1
rmdir testdir

# Test 13: Output file is a directory
mkdir outdir
run_test "Output file is a directory" \
         "./pipex infile \"cat\" \"wc -l\" outdir" \
         "Error: Output file is a directory" \
         1
rmdir outdir


# # Memory leak test
# if command -v valgrind &> /dev/null; then
#     echo "Running memory leak test..."
#     valgrind --leak-check=full --error-exitcode=1 ./pipex infile "cat" "wc -l" outfile
#     if [ $? -eq 0 ]; then
#         echo -e "${GREEN}No memory leaks detected${NC}"
#     else
#         echo -e "${RED}Memory leaks detected${NC}"
#     fi
# else
#     echo "Valgrind not installed, skipping memory leak test"
# fi

# Clean up
make fclean