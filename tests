#!/bin/bash

testDir="TestFiles"
# Store all test files in array
files="$(ls $testDir)"

# Loop through each file and test sha512 output
for t in ${files[@]}; do
    echo "Checking file $t"
    expec="$(sha512sum $testDir/$t)"
    myout="$(./sha512 -p $testDir/$t)  $testDir/$t"
    echo "Expected: " $expec
    echo "Output:   " $myout
    if [[ $myout == $expec ]]; then
        echo "Pass"
    else
        echo "Fail"
    fi
done
