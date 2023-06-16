#!/bin/bash

#########################################Config variables that need to be set for set of big trees####################



Output_base_name="JetMET0__Run2023C-PromptReco-v4__AK4PUPPI_new"

splitted_list_base_name="lists/2023_promptreco/list_JetMET0_Run2022C-PromptReco-v4"

cutFile="config/cutFile_4jets_AK4PUPPI.txt"

Analyzer="analysisClass_4Jets_minDeltaR_AK4PUPPI.C"


Release="CMSSW_13_0_3"
Release_local_path="/afs/cern.ch/work/i/izisopou/public/4jets_Run3/CMSSW_13_0_3"
Architecture="slc7_amd64_gcc11"

#####################################################################################################################


usage ()
{
	echo ""
	echo "Arguments for script \"$0\" were given incorrectly or missing! Check the Usage & Example"
	echo ""
	echo "Usage:   $0 -list_No 'Number_of_first_list_to_be_submited' -dir Output_directory -log_dir log_files_directory"

	echo "Example: $0 -list_No 0 -dir /eos/cms/store/user/dkarasav/JetHT_Run2018-reReco_reduced_trees/JetHT__Run2018A-17Sep2018-v1__MINIAOD/ -log_dir Condor_Outputs/JetHT__Run2018A-17Sep2018-v1__MINIAOD/"

	echo ""
	exit 1;
}


#if [ $# -ne 3 ]; then usage; fi;
while [ $# -gt 0 ]; # till there are parameters
do
  case "$1" in
    -list_No) list_No="$2"; shift ;;
    -dir) directory="$2"; shift ;;
    -log_dir) log_directory="$2"; shift ;;
    *) usage ;;
  esac
  shift  # get following parameters
done


	# if a config list with the same name exists in the log directory, it gets deleted to replace it.
	if test -f "$log_directory"/config_file_"$list_No".txt; then
    	rm "$log_directory"/config_file_"$list_No".txt
	fi


	echo "directory=\""$directory"/\"" 									>>	 "$log_directory"/config_file_"$list_No".txt
	echo "Output_base_name=\""$Output_base_name"\"" 					>>	 "$log_directory"/config_file_"$list_No".txt
	echo "list_name=\""$splitted_list_base_name"_"$list_No"of10.txt\"" 		>>	 "$log_directory"/config_file_"$list_No".txt
	echo "cutFile=\""$cutFile"\"" 										>>	 "$log_directory"/config_file_"$list_No".txt
	echo "Release=\""$Release"\"" 										>>	 "$log_directory"/config_file_"$list_No".txt
	echo "Release_local_path=\""$Release_local_path"\"" 				>>	 "$log_directory"/config_file_"$list_No".txt
	echo "Analyzer=\""$Analyzer"\"" 									>>	 "$log_directory"/config_file_"$list_No".txt
	echo "Architecture=\""$Architecture"\"" 							>>	 "$log_directory"/config_file_"$list_No".txt
	echo "list_No=\""$list_No"\"" 										>>	 "$log_directory"/config_file_"$list_No".txt

	
