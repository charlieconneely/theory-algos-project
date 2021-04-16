#!/bin/bash

# Store all test files in array
files="$(ls TestFiles)"

# Loop through each file and test sha512 output
for t in ${files[@]}; do
    echo "Checking file $t"   
    expec="$(sha512sum TestFiles/$t)"
    myout="$(./sha512 -p TestFiles/$t)  TestFiles/$t"
    echo "Expected: " $expec
    echo "Output:   " $myout
    if [[ $myout == $expec ]]; then
        echo "Pass"
    else
        echo "Fail"
    fi
done
