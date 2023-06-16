#!/bin/bash

#this script makes lists (.txt) -of chosen size- of the big tree root files stored in a directory




#Example: ./create_small_lists.sh -path /eos/cms/store/user/dkarasav/MinBias_2018_RunC_big_trees/MinimumBias/crab_MinimumBias__Run2018C-PromptReco-v3__MINIAOD/181107_143918 -name MinimumBias__Run2018C-PromptReco-v3__MINIAOD -size 50 -dir Test_directory


#This will split the list "lists/promptReco_2018/list_promtreco_run2018D_whole.txt" in smaller lists with name: lists/promptReco_2018/list_promtreco_run2018D_0.txt, lists/promptReco_2018/list_promtreco_run2018D_1.txt , ... 
#Each splitted list will have 50 big trees

usage ()
{
	echo ""
	echo "Arguments given incorrectly or missing! Check the Usage & Example"
	echo ""
	echo "Usage:   $0 -path Path_to_big_trees -name name_of_output_splitted_lists -size No_of_files_per_list -dir Output_directory"

	echo "Example: $0 -path /eos/cms/store/user/dkarasav/MinBias_2018_RunC_big_trees/MinimumBias/crab_MinimumBias__Run2018C-PromptReco-v3__MINIAOD/181107_143918 -name MinimumBias__Run2018C-PromptReco-v3__MINIAOD -size 50 -dir lists/test_directory"

	echo ""
	exit 1;
}



if [ $# -le 3 ]; then usage; fi;
while [ $# -gt 0 ]; # till there are parameters
do
  case "$1" in
    -path) path_to_big_trees="$2"; shift ;;
    -name) splitted_list_base_name="$2"; shift ;;
    -size) split_size="$2"; shift ;;
    -dir) output_directory="$2"; shift ;;
    *) usage ;;
  esac
  shift  # get following parameters
done

echo ""
echo 'Path of big trees: '$path_to_big_trees
echo 'Name of outputs: '$splitted_list_base_name
echo "Split size: $split_size"
echo 'Output: '$output_directory




###### The splitting starts here #################

mkdir "$output_directory"

ls -d -1 "$path_to_big_trees"/*/*.root | sort -V >> lists/"$splitted_list_base_name"_big_list.txt

big_list_txt="lists/"$splitted_list_base_name"_big_list.txt"

split -l $split_size --numeric-suffixes "$big_list_txt" "$splitted_list_base_name"_

Number_of_big_trees=$(wc -l < $big_list_txt)

Number_of_splitted_files=$(($Number_of_big_trees / $split_size))

current_file=0

	while (( $current_file < $Number_of_splitted_files + 1 ))
	do
		if (( $current_file < 10 ))
		then
			mv "$splitted_list_base_name"_0"$current_file" "$output_directory"/"$splitted_list_base_name"_"$current_file".txt 
		fi

		if (( $current_file >= 10 ))
		then
			mv "$splitted_list_base_name"_"$current_file" "$output_directory"/"$splitted_list_base_name"_"$current_file".txt
		fi		

		current_file=$(( current_file+1 ))
	done

mv "$big_list_txt" "$output_directory"/


#ls -d -1 ~/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/santanas/crab_JetHT__Run2015D-PromptReco-v3__MINIAOD__151012_071719/*.root | sort -V >> lists/2015D.txt
