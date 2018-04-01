#!/bin/bash

trap : SIGINT

main()
{
	arg_size=$#
    args=("$@")
    cptest utils is_problem_dir
    if [ $? -eq 0 ]
    then
        test_num=$(printf "%03d" $(($(/opt/cptest/bin/cptest_start utils test_count) + 1)))
        test_folder=$(/opt/cptest/bin/cptest_start utils test_folder)
        input_file="./${test_folder}/${test_num}.dat"
        output_file="./${test_folder}/${test_num}.ans"
        echo "Input: [ctrl+d to submit]"
        cat > ${input_file}
        echo "Output [ctrl+d to submit]"
        cat > ${output_file}
        echo "Test was saved with number ${test_num}"
    else
        echo "No test archive"
        echo "Use 'cptest init' to create archive"
    fi
}

main $@
