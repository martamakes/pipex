#!/bin/bash

# Remove input files
rm -f infile longtest.txt specialtest.txt verylongfile.txt
rm -f no_permission_file no_write_permission

# Remove output files
rm -f outfile outfile_bash

# Remove directories created by tests
rm -rf output testdir outdir

# Remove files created by bonus test
rm -rf output

echo "Cleanup complete."