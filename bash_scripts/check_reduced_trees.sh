#!/bin/bash

path_to_reduced_trees=$1


ls -d -1 "$path_to_reduced_trees"/*reduced*.root | sort -V >> temporary_file_with_paths.txt

Number_of_root_files=$(wc -l < temporary_file_with_paths.txt)

#source produce_reduced_trees_config.txt
#echo $work
#echo "$list_No"

current_path=$(pwd)

if [ "$Number_of_root_files" -eq "0" ]
then
	echo " "
	echo "This directory does not contain any reduced .root files. Please give a directory that contains reduced tree files."
	echo " "
	exit
fi 

echo " "
echo " The directory contains" "$Number_of_root_files" "reduced root files. Checking if they closed succesfully..." 
echo " "

filename="temporary_file_with_paths.txt"
while read -r line; do
    name="\"$line\""

	root -l -q "$current_path/bash_scripts/Open_and_close_root_file.C("$name")" &>> temp_file_of_stdout.txt #Opens and closes each root file in the directory and writes in a txt file the terminal output.

done < "$filename"

echo " "
Output_of_grep=$(grep "Error\|recover\|Warning" temp_file_of_stdout.txt) #grep's the txt file and writes output in variable 

if [  -z "$Output_of_grep" ];  #true if the variable is empty
then
	echo "All files were closed correctly! Good job! "
	echo ""
	echo "\ (•◡ •) /"
fi
if [  -n "$Output_of_grep" ]; #true if variable is non-empty
then
	echo "Careful! Some files did not close correctly, take a look at the errors/warnings: "
	echo " "
	echo "ᕦ(ò_óˇ)ᕤ"
	echo " "
	grep "Error\|recover\|Warning" temp_file_of_stdout.txt
fi
echo " "

#rm temp_file_of_stdout.txt
rm temporary_file_with_paths.txt
