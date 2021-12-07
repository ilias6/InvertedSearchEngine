#!/bin/bash

commands=$2;

files=$(ls -p | grep -v /);

for f in $files
do
	vim -s $commands $f
done
