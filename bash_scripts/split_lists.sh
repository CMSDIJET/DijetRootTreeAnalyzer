#!/bin/bash

#this script splits a .txt file with a big list of big trees to smaller ones whose size and name you define

#Arguments: arg1 = big_list_name , arg2 = base_name_of_small_lists , arg3 = size of small lists 
#Example: ./split_lists.sh lists/promptReco_2018/list_promtreco_run2018D_whole.txt lists/promptReco_2018/list_promtreco_run2018D 50
#This will split the list "lists/promptReco_2018/list_promtreco_run2018D_whole.txt" in smaller lists with name: lists/promptReco_2018/list_promtreco_run2018D_0.txt, lists/promptReco_2018/list_promtreco_run2018D_1.txt , ... 
#Each splitted list will have 50 big trees


big_list_txt=$1

splitted_list_base_name=$2

split_size=$3

split -l $split_size --numeric-suffixes "$big_list_txt" "$splitted_list_base_name"_

Number_of_big_trees=$(wc -l < $big_list_txt)

Number_of_splitted_files=$(($Number_of_big_trees / $split_size))

current_file=0

	while (( $current_file < $Number_of_splitted_files + 1 ))
	do
		if (( $current_file < 10 ))
		then
		mv "$splitted_list_base_name"_0"$current_file" "$splitted_list_base_name"_"$current_file".txt 
		fi

		if (( $current_file >= 10 ))
		then
		mv "$splitted_list_base_name"_"$current_file" "$splitted_list_base_name"_"$current_file".txt
		fi		

		current_file=$(( current_file+1 ))
	done

