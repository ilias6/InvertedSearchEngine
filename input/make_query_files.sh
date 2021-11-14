#!/bin/bash
if [ $(($#)) -ne 3 ]; then
    echo "Usage: $0 numOfFiles MaxWordsInFile";
    exit 1;
fi
queriesDirName="queries/"
mkdir -p $queriesDirName;
fileName="query_"

#for i in {0..10000}; do
#rm "./${queriesDirName}${fileName}${i}";
#done
rm "./$queriesDirName"*;

totalFiles=$(($2));
maxWords=$(($3));
fileCounter=0;

maxWordsInFile=0;
wordCounter=0;
flagg=0;
# touch "${queriesDirName}${fileName}${fileCounter}";
# fileCounter=$(($fileCounter + 1));

while read line; do
    for word in $line; do
	wordCounter=$(($wordCounter + 1));
	if [ $(($RANDOM % $maxWords)) -eq 0 ] && [ $(($flagg)) -ne 0 ]; then
	    touch "${queriesDirName}${fileName}${fileCounter}"
	    fileCounter=$(($fileCounter + 1));
	    if [ $(($wordCounter)) -ge $(($maxWordsInFile)) ]; then
		maxWordsInFile=$(($wordCounter));
	    fi
	    if [ $(($fileCounter)) -ge $(($totalFiles)) ]; then
		flag=1;
		break;
	    fi
	    wordCounter=0;
	fi
    flagg=1;
	if [ $(($wordCounter)) -ge $(($maxWords)) ]; then
	    touch "${queriesDirName}${fileName}${fileCounter}"
	    fileCounter=$(($fileCounter + 1));
	    if [ $(($wordCounter)) -ge $(($maxWordsInFile)) ]; then
		maxWordsInFile=$(($wordCounter));
	    fi

	    if [ $(($fileCounter)) -ge $(($totalFiles)) ]; then
		flag=1;
		break;
	    fi

	    wordCounter=0;
	fi
	echo $word >> "${queriesDirName}${fileName}${fileCounter-1}"
    done
    if [ $(($flag)) -eq 1 ]; then
	break;
    fi
done < $1

echo "Total files: ${fileCounter}";
echo "Max words in file: ${maxWordsInFile}";
