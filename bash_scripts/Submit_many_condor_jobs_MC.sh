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
	echo "Usage:   $0 -i 'Number_of_first_list_to_be_submited' -f 'Number_of_last_list_to_be_submited' -pT_bin_low 15 -pT_bin_high 30 -dir 'Output_directory' -log_dir log_file_directory -job_time 'tomorrow'"
	echo ""
	echo "Example: $0 -i 0 -f 8 -pT_bin_low 15 -pT_bin_high 30 -dir /eos/cms/store/user/dkarasav/JetHT_Run2018-reReco_reduced_trees/JetHT__Run2018A-17Sep2018-v1__MINIAOD/ -log_dir Condor_Outputs/JetHT__Run2018A-17Sep2018-v1__MINIAOD -job_time tomorrow"

	echo ""
	exit 1;
}


#if [ $# -ne 5 ]; then usage; fi;
while [ $# -gt 0 ]; # till there are parameters
do
  case "$1" in
	-job_time) job_time="$2"; shift ;; 
    -i) first_list_No="$2"; shift ;;
    -f) last_list_No="$2"; shift ;;
	-pT_bin_low) PtHatBin_start="$2"; shift ;;
    -pT_bin_high) PtHatBin_end="$2"; shift ;;
    -dir) output_directory="$2"; shift ;;
    -log_dir) log_directory="$2"; shift ;;
    *) usage ;;
  esac
  shift  # get following parameters
done

if [ -z "$first_list_No" ] || [ -z "$last_list_No" ] || [ -z "$output_directory" ] || [ -z "$log_directory" ] || [ -z "$job_time" ] || [ -z "$PtHatBin_start" ] || [ -z "$PtHatBin_end" ];  #true if any argument is empty
then
	usage;
fi

Full_path_to_DijetRootTreeAnalyzer=$(pwd)

echo ""
echo 'First list number: '$first_list_No
echo 'Last list number: '$last_list_No
echo 'pT hat Bin: '$PtHatBin_start'-'$PtHatBin_end
echo 'Output destination: '$output_directory
echo 'Log file destination: '$log_directory
echo 'Path to current DijetRootTreeAnalyzer: '$Full_path_to_DijetRootTreeAnalyzer
echo 'Job max time: '$job_time


echo ""
echo "Waiting 5 seconds. Check your arguments...!"
echo ""
sleep 5;



#############submitting_each_job##############

list_No=$first_list_No


#mkdir Condor_Outputs
log_dir_bin=$log_directory"/"$PtHatBin_start"to"$PtHatBin_end
mkdir "$log_directory"
mkdir "$log_dir_bin"

echo ""
echo "You could say... the job submission has... "
echo " "
echo "(•_•)   ( •_•)>⌐■-■   (⌐■ _■ )"
echo ""
echo "Begun!"



while (( $list_No < $last_list_No +1 ))
	do
		echo ""
		echo "Submitting list number: ""$list_No""..."
		
		source bash_scripts/create_list_config_MC.sh -list_No "$list_No" -dir "$output_directory" -log_dir "$log_dir_bin" -pT_bin_low "$PtHatBin_start" -pT_bin_high "$PtHatBin_end"
		source bash_scripts/create_condor_setup_MC.sh -list_No "$list_No" -log_dir "$log_dir_bin" -path "$Full_path_to_DijetRootTreeAnalyzer" -job_time "$job_time"

		###################################
		# define paths
		###################################
		         
		mkdir "$log_dir_bin"/log_"$list_No"
		#mkdir "$log_dir_bin"/out_"$list_No"
		#mkdir "$log_dir_bin"/err_"$list_No"
		chmod ugo+rwx "$log_dir_bin"/condor_setup_job_"$list_No".sub
		condor_submit "$log_dir_bin"/condor_setup_job_"$list_No".sub

	

		list_No=$(( list_No+1 ))
	done

