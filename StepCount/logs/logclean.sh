#!/bin/bash -e

while getopts f: option
do 
    case "${option}"
        in
        f)filename=${OPTARG};;
    esac
done

echo "Filename: $filename"

TOTAL=$(wc -l <$filename)
echo $TOTAL
sed -i 1d $filename
sed -i "$TOTAL d" $filename
