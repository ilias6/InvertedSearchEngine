#!/bin/bash

bin/out input/small_test.txt
while [ $? -ne 139 ]
do
    bin/out input/small_test.txt
done
