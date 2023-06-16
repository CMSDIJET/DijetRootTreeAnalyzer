#!/bin/bash


##########################Getting input variables##################################

usage ()
{
	echo ""
	echo "Arguments for script \"$0\" were given incorrectly or missing! Check the Usage & Example"
	echo ""
	echo "Usage:   $0 -list_No 'Number_of_first_list_to_be_submited' -log_dir log_files_directory -path 'path_to_currect_DijetRootTreeAnalyzer'"

	echo "Example: $0 -list_No 0 -log_dir Condor_Outputs/logs_JetHT__Run2018A-17Sep2018-v1__MINIAOD/ -path /afs/cern.ch/work/d/dkarasav/public/CMSSW_10_1_5/src/CMSDIJET/DijetRootTreeAnalyzer/"

	echo ""
	exit 1;
}


#if [ $# -ne 3 ]; then usage; fi;
while [ $# -gt 0 ]; # till there are parameters
do
  case "$1" in
    -list_No) list_No="$2"; shift ;;
    -log_dir) log_directory="$2"; shift ;;
	-path) Full_path_to_DijetRootTreeAnalyzer="$2"; shift ;;  
	-job_time) job_time="$2"; shift ;; 
    *) usage ;;
  esac
  shift  # get following parameters
done


#############################################################Creates the .sub file for condor submition #######################################

	# if a condor setup file with the same name exists in the log directory, it gets deleted and replaced it.
	if test -f "$log_directory"/condor_setup_job_"$list_No".sub; then
    	rm "$log_directory"/condor_setup_job_"$list_No".sub
	fi


	echo "executable              = bash_scripts/produce_reduced_trees.sh" 															>> "$log_directory"/condor_setup_job_"$list_No".sub
	echo "output                  = "$log_directory"/log_"$list_No"/Output.\$(ClusterId).\$(ProcId).out" 				>> "$log_directory"/condor_setup_job_"$list_No".sub
	echo "error                  = "$log_directory"/log_"$list_No"/Error.\$(ClusterId).\$(ProcId).err"					>> "$log_directory"/condor_setup_job_"$list_No".sub
	echo "log                  = "$log_directory"/log_"$list_No"/Log.\$(ClusterId).\$(ProcId).log" 						>> "$log_directory"/condor_setup_job_"$list_No".sub
	echo "+JobFlavour 	          = \""$job_time"\"" 																	>> "$log_directory"/condor_setup_job_"$list_No".sub
	echo "should_transfer_files   = YES" 																				>> "$log_directory"/condor_setup_job_"$list_No".sub
	echo "when_to_transfer_output = ON_EXIT" 																			>> "$log_directory"/condor_setup_job_"$list_No".sub
	echo " " 																											>> "$log_directory"/condor_setup_job_"$list_No".sub
	echo "Arguments          = "$log_directory"/config_file_"$list_No".txt ""$Full_path_to_DijetRootTreeAnalyzer" " 0"  >> "$log_directory"/condor_setup_job_"$list_No".sub
	echo "queue" 																										>> "$log_directory"/condor_setup_job_"$list_No".sub


