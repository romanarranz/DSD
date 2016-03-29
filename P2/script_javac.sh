#!/bin/bash

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

output=""
i=0
while (( i++ <= ${#DIR} ))
do
   	char=$(expr substr "$DIR" $i 1)
   	if [ "$char" == " " ] || [ "$char" == "[" ] || [ "$char" == "]" ] ; then
   		output="$output\\$char"
   	else
   		output="$output$char"
   	fi
done

dataSrc="$DIR/src"
outputDir="$output/bin"

echo "Borrando archivos ejecutables ..."
rm "$outputDir/*"

echo "Creando archivos ejecutables ..."
javac -d "$outputDir" "$dataSrc/*.java"