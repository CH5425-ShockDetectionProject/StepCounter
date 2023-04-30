#!/bin/bash -e

while getopts f: option
do 
    case "${option}"
        in
        f)filename=${OPTARG};;
    esac
done

echo "Filename: $filename"

sed -i 1d $filename
TOTAL=$(wc -l <$filename)
echo $TOTAL
sed -i "$TOTAL d" $filename
