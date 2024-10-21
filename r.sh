#!/bin/bash

# Author information
#   Author name : Kshitij Pingle
#   Author email: kpingle@csu.fullerton.edu
#   Author section: 351-13
#   Author CWID : 885626978 


# compile the program
gcc -o thready thready.c

# Check if we want to run tests
if [ "$1" == "test" ]; then
    # Run the tests
    ( echo -e 'Pattern 1 :'; 
      ./thready 1 6;
      echo -e '\nPattern 2 :';
      ./thready 2 6; ) > results.txt
fi