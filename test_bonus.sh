#!/bin/bash
$(count=0)
$(rm -rf output)
$(mkdir output)
$(ls -la > infile)
$(valgrind >/dev/null 2>&1)
val=$?

echo '================================================================'
echo '                     Norminette check'
echo '================================================================'
norminette ../ | grep "Error"
ret=$?
if [[ $ret -eq 1 ]]; then
	echo "$(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "$(tput setaf 1)[KO]$(tput sgr 0)"
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '          Test '$count' >> Forbidden function check'
echo '================================================================'
if [[ $(uname) = "Linux" ]]; then
    nm -un pipex | grep ' T ' | awk '{print $3}' | sort > fn_used
else
    nm -un pipex | grep ' T ' | awk '{print $3}' | sort > fn_used
fi

# Get the allowed functions and sort them
sort fn_allowed > fn_allowed_sorted

# Find functions that are used but not allowed
comm -13 fn_allowed_sorted fn_used > unauthorized_funcs

if [ -s unauthorized_funcs ]; then
    echo "Unauthorized functions found:"
    cat unauthorized_funcs
    echo "$(tput setaf 1)[KO]$(tput sgr 0)"
else
    echo "$(tput setaf 2)[OK]$(tput sgr 0)"
fi

# Clean up
rm fn_used fn_allowed_sorted unauthorized_funcs

sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '             Test' $count ">> Check the executable"
echo '             Executable name is pipex_bonus'
echo '================================================================'
if [ ! -f "pipex_bonus" ]; then
	echo "$(tput setaf 1)[KO]$(tput sgr 0)"
	echo
	exit 0
else
	echo "$(tput setaf 2)[OK]$(tput sgr 0)"
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '        Test' $count ">> Invalid number of arguments"
echo '                    ./pipex_bonus infile'
echo '================================================================'
echo "<"; ./pipex_bonus infile
if [[ $val != 127 ]]; then
	echo
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus infile >/dev/null 2>&1
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '        Test' $count ">> Multiple pipes"
echo './pipex_bonus infile "cat" "grep a" "wc -l" output/outfile'${count}''
echo '================================================================'
echo "<"; ./pipex_bonus infile "cat" "grep a" "wc -l" "output/outfile${count}"
exit=$?
echo
echo ">"; < infile cat | grep a | wc -l > "output/outfile${count}-orig"
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "<" $exit
	echo ">" $exit_orig
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi
if [[ $val != 127 ]]; then
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus infile "cat" "grep a" "wc -l" output/valgrind >/dev/null 2>&1
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '        Test' $count ">> Here_doc basic"
echo './pipex_bonus here_doc END "cat" "wc -l" output/outfile'${count}''
echo '================================================================'
echo "<"; ./pipex_bonus here_doc END "cat" "wc -l" "output/outfile${count}" << EOF
Hello
World
This is a test
END
EOF
exit=$?
echo
echo ">"; cat << EOF | cat | wc -l > "output/outfile${count}-orig"
Hello
World
This is a test
END
EOF
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "<" $exit
	echo ">" $exit_orig
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi
if [[ $val != 127 ]]; then
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus here_doc END "cat" "wc -l" output/valgrind << EOF >/dev/null 2>&1
Hello
World
This is a test
END
EOF
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '        Test' $count ">> Here_doc with multiple pipes"
echo './pipex_bonus here_doc END "grep a" "tr a-z A-Z" "wc -l" output/outfile'${count}''
echo '================================================================'
echo "<"; ./pipex_bonus here_doc END "grep a" "tr a-z A-Z" "wc -l" "output/outfile${count}" << EOF
Hello
World
apple
banana
END
EOF
exit=$?
echo
echo ">"; cat << EOF | grep a | tr a-z A-Z | wc -l > "output/outfile${count}-orig"
Hello
World
apple
banana
END
EOF
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "<" $exit
	echo ">" $exit_orig
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi
if [[ $val != 127 ]]; then
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus here_doc END "grep a" "tr a-z A-Z" "wc -l" output/valgrind << EOF >/dev/null 2>&1
Hello
World
apple
banana
END
EOF
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '        Test' $count ">> Multiple pipes with file input"
echo './pipex_bonus infile "cat" "grep a" "tr a-z A-Z" "wc -l" output/outfile'${count}''
echo '================================================================'
echo "<"; ./pipex_bonus infile "cat" "grep a" "tr a-z A-Z" "wc -l" "output/outfile${count}"
exit=$?
echo
echo ">"; < infile cat | grep a | tr a-z A-Z | wc -l > "output/outfile${count}-orig"
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "<" $exit
	echo ">" $exit_orig
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi
if [[ $val != 127 ]]; then
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus infile "cat" "grep a" "tr a-z A-Z" "wc -l" output/valgrind >/dev/null 2>&1
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '        Test' $count ">> Invalid file with multiple pipes"
echo './pipex_bonus nonexistent "cat" "grep a" "wc -l" output/outfile'${count}''
echo '================================================================'
echo "<"; ./pipex_bonus nonexistent "cat" "grep a" "wc -l" "output/outfile${count}"
exit=$?
echo
echo ">"; < nonexistent cat | grep a | wc -l > "output/outfile${count}-orig"
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "<" $exit
	echo ">" $exit_orig
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi
if [[ $val != 127 ]]; then
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus nonexistent "cat" "grep a" "wc -l" output/valgrind >/dev/null 2>&1
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
sleep 1

echo
count=$((count+1))
echo '================================================================'
echo '        Test' $count ">> Invalid command with multiple pipes"
echo './pipex_bonus infile "cat" "grp a" "wc -l" output/outfile'${count}''
echo '================================================================'
echo "<"; ./pipex_bonus infile "cat" "grp a" "wc -l" "output/outfile${count}"
exit=$?
echo
echo ">"; < infile cat | grp a | wc -l > "output/outfile${count}-orig"
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "<" $exit
	echo ">" $exit_orig
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi
if [[ $val != 127 ]]; then
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus infile "cat" "grp a" "wc -l" output/valgrind >/dev/null 2>&1
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi
sleep 1

echo
echo '~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'
echo '                   >>>>>> Extra Tests <<<<<<'
echo '             Kudos if you handled these situations'
echo '~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'

echo
count=$((count+1))
echo '================================================================'
echo '        Test' $count ">> Many pipes"
echo './pipex_bonus infile "cat" "grep a" "sed s/a/A/" "tr A Z" "sort" "uniq" output/outfile'${count}''
echo '================================================================'
echo "<"; ./pipex_bonus infile "cat" "grep a" "sed s/a/A/" "tr A Z" "sort" "uniq" "output/outfile${count}"
exit=$?
echo
echo ">"; < infile cat | grep a | sed s/a/A/ | tr A Z | sort | uniq > "output/outfile${count}-orig"
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
	echo "<" $exit
	echo ">" $exit_orig
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi
if [[ $val != 127 ]]; then
	valgrind --leak-check=full --log-file="output/valgrind${count}" ./pipex_bonus infile "cat" "grep a" "sed s/a/A/" "tr A Z" "sort" "uniq" output/valgrind >/dev/null 2>&1
	< output/valgrind${count} grep "still reachable"
	ret=$?
	if [[ $ret -eq 1 ]]; then
    	echo "memory leak $(tput setaf 2)[OK]$(tput sgr 0)"
	else
    	echo "memory leak $(tput setaf 1)[KO]$(tput sgr 0)"
	fi
fi

echo

$(rm -f output/valgrind)

#!/bin/bash

# ... [Previous content remains the same] ...

echo
count=$((count+1))
echo '================================================================'
echo '        Test' $count ">> Here_doc with special characters in limiter"
echo './pipex_bonus here_doc "END$$$" "cat" "grep Hello" output/outfile'${count}''
echo '================================================================'
echo "<"; ./pipex_bonus here_doc "END$$$" "cat" "grep Hello" "output/outfile${count}" << EOF
Hello
World
This is a test
END$$$
EOF
exit=$?
echo
echo ">"; cat << EOF | cat | grep Hello > "output/outfile${count}-orig"
Hello
World
This is a test
END$$$
EOF
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi

echo
count=$((count+1))
echo '================================================================'
echo '        Test' $count ">> Many pipes (10 pipes)"
echo './pipex_bonus infile "cat" "grep a" "sed s/a/A/" "tr A Z" "sort" "uniq" "wc -l" "awk {print $1}" "bc" "factor" output/outfile'${count}''
echo '================================================================'
echo "<"; ./pipex_bonus infile "cat" "grep a" "sed s/a/A/" "tr A Z" "sort" "uniq" "wc -l" "awk {print $1}" "bc" "factor" "output/outfile${count}"
exit=$?
echo
echo ">"; < infile cat | grep a | sed s/a/A/ | tr A Z | sort | uniq | wc -l | awk '{print $1}' | bc | factor > "output/outfile${count}-orig"
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi

echo
count=$((count+1))
echo '================================================================'
echo '        Test' $count ">> Here_doc with empty input"
echo './pipex_bonus here_doc END "cat" "wc -l" output/outfile'${count}''
echo '================================================================'
echo "<"; ./pipex_bonus here_doc END "cat" "wc -l" "output/outfile${count}" << EOF
END
EOF
exit=$?
echo
echo ">"; cat << EOF | cat | wc -l > "output/outfile${count}-orig"
END
EOF
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi

echo
count=$((count+1))
echo '================================================================'
echo '        Test' $count ">> Command with environment variables"
echo './pipex_bonus infile "env" "grep PATH" "wc -l" output/outfile'${count}''
echo '================================================================'
echo "<"; ./pipex_bonus infile "env" "grep PATH" "wc -l" "output/outfile${count}"
exit=$?
echo
echo ">"; < infile env | grep PATH | wc -l > "output/outfile${count}-orig"
exit_orig=$?
echo
if [[ $exit = $exit_orig ]]; then
    echo "exit code $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "exit code $(tput setaf 1)[KO]$(tput sgr 0)"
fi
diff "output/outfile${count}" "output/outfile${count}-orig"
ret=$?
if [[ $ret -eq 0 ]]; then
    echo "cmd output $(tput setaf 2)[OK]$(tput sgr 0)"
else
    echo "cmd output $(tput setaf 1)[KO]$(tput sgr 0)"
fi
