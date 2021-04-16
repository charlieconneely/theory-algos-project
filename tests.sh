#!/bin/bash

echo "Checking file test1.txt."   
expec="$(sha512sum TestFiles/test1.txt)"
myout="$(./sha512 -p TestFiles/test1.txt)  TestFiles/test1.txt"
echo "Expected: " $expec
echo "Output:   " $myout
if [[ $myout == $expec ]]; then
    echo "Pass"
else
    echo "Fail"
fi