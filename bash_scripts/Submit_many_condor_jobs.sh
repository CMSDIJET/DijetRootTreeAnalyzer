#!/bin/bash
###################################
#getting arguments
###################################

usage ()
{
	echo ""
	echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!"
	echo ""
	echo "Arguments for script \"$0\" were given incorrectly or missing (5 arguments required) ! Check the Usage & Example"
	echo ""
	echo "Usage:   $0 -i 'Number_of_first_list_to_be_submited' -f 'Number_of_last_list_to_be_submited' -dir 'Output_directory' -log_dir log_file_directory -job_time 'tomorrow'"

	echo "Example: $0 -i 0 -f 8 -dir /eos/cms/store/user/dkarasav/JetHT_Run2018-reReco_reduced_trees/JetHT__Run2018A-17Sep2018-v1__MINIAOD/ -log_dir Condor_Outputs/JetHT__Run2018A-17Sep2018-v1__MINIAOD -job_time tomorrow"

	echo ""
	exit 1;
}


#Other choices for job time are: 
#	espresso     = 20 minutes
#	microcentury = 1 hour
#	longlunch    = 2 hours
#	workday      = 8 hours
#	tomorrow     = 1 day
#	testmatch    = 3 days
#	nextweek     = 1 week



#if [ $# -ne 5 ]; then usage; fi;
while [ $# -gt 0 ]; # till there are parameters
do
  case "$1" in
    -i) first_list_No="$2"; shift ;;
    -f) last_list_No="$2"; shift ;;
    -dir) output_directory="$2"; shift ;;
    -log_dir) log_directory="$2"; shift ;;
    -job_time) job_time="$2"; shift ;;
    *) usage ;;
  esac
  shift  # get following parameters
done





Full_path_to_DijetRootTreeAnalyzer=$(pwd)

echo ""
echo "Arguments given: "
echo 'First list number: '$first_list_No
echo 'Last list number: '$last_list_No
echo 'Output destination: '$output_directory
echo 'Log file destination: '$log_directory
echo 'Job time: '$job_time
echo 'Path to current DijetRootTreeAnalyzer: '$Full_path_to_DijetRootTreeAnalyzer


if [ -z "$first_list_No" ] || [ -z "$last_list_No" ] || [ -z "$output_directory" ] || [ -z "$log_directory" ] || [ -z "$job_time" ] ;  #true if any argument is empty
then
	usage;
fi



echo ""
echo "Waiting 5 seconds. Check your arguments...!"
echo ""
sleep 5;

#############submitting_each_job##############

list_No=$first_list_No


#mkdir Condor_Outputs
mkdir "$log_directory"


echo ""
echo "You could say... the job submission has... "
echo " "
echo "(•_•)   ( •_•)>⌐■-■   (⌐■ _■ )"
echo ""
echo "Begun!"



while (( $list_No < $last_list_No +1 ))
	do
		echo ""
		echo "Submitting list number:""$list_No""..."
		
		source bash_scripts/create_list_config.sh -list_No "$list_No" -dir "$output_directory" -log_dir "$log_directory"
		source bash_scripts/create_condor_setup.sh -list_No "$list_No" -log_dir "$log_directory" -path "$Full_path_to_DijetRootTreeAnalyzer" -job_time "$job_time"

		###################################
		# define paths
		###################################
		         
		mkdir "$log_directory"/log_"$list_No"
		#mkdir "$log_directory"/out_"$list_No"
		#mkdir "$log_directory"/err_"$list_No"
		chmod ugo+rwx "$log_directory"/condor_setup_job_"$list_No".sub
		condor_submit "$log_directory"/condor_setup_job_"$list_No".sub

	

		list_No=$(( list_No+1 ))
	done

