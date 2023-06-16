#!/bin/bash

#########################################Config variables that need to be set right for each set of big trees####################

Output_base_name_without_ptbins="TuneCP5_13p6TeV_pythia8__Run3Summer22EEMiniAODv3-124X_mcRun3_2022_realistic_postEE_v1_ext1-v2__AK4PUPPI"       #(eg QCD_TuneCP5_13TeV_pythia8_noJetID) 
#splitted_list_base_name="lists/2022_QCDMC/list_Run3Summer22EE_PT-120to170"   #this is not used currently -"list name" is defined in line 61

cutFile="config/cutFile_4jets_AK4PUPPI_MC.txt"

Analyzer="analysisClass_4Jets_minDeltaR_AK4PUPPI_QCDMC.C"

Architecture="slc7_amd64_gcc11"
Release="CMSSW_13_0_3"
Release_local_path="/afs/cern.ch/work/i/izisopou/public/4jets_Run3/CMSSW_13_0_3"

#####################################################################################################################


usage ()
{
	echo ""
	echo "Arguments for script \"$0\" were given incorrectly or missing! Check the Usage & Example"
	echo ""
	echo "Usage:   $0 -list_No 'Number_of_first_list_to_be_submited' -pT_bin_low 15 -pT_bin_high 30 -dir Output_directory -log_dir log_files_directory "

	echo "Example: $0 -list_No 0 -pT_bin_low 15 -pT_bin_high 30 -dir /eos/cms/store/user/dkarasav/JetHT_Run2018-reReco_reduced_trees/JetHT__Run2018A-17Sep2018-v1__MINIAOD/ -log_dir Condor_Outputs/JetHT__Run2018A-17Sep2018-v1__MINIAOD/"

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
    -pT_bin_low) PtHatBin_start="$2"; shift ;;
    -pT_bin_high) PtHatBin_end="$2"; shift ;;
    *) usage ;;
  esac
  shift  # get following parameters
done


#Output_base_name="QCD_Pt_"$PtHatBin_start"to"$PtHatBin_end"_TuneCP5_13TeV_pythia8_JetID"

	if test -f "$log_directory"/config_file_"$list_No".txt; then
    	rm "$log_directory"/config_file_"$list_No".txt
	fi

	echo "directory=\""$directory"/\""																					>> "$log_directory"/config_file_"$list_No".txt
	echo "Output_base_name=\"QCD_PT-"$PtHatBin_start"to"$PtHatBin_end"_"$Output_base_name_without_ptbins"\"" 				>> "$log_directory"/config_file_"$list_No".txt

	echo "list_name=\"lists/2022_QCDMC/list_Run3Summer22EE_PT-"$PtHatBin_start"to"$PtHatBin_end"_"$list_No"of10.txt\""						>> "$log_directory"/config_file_"$list_No".txt

	echo "cutFile=\""$cutFile"\"" 																						>> "$log_directory"/config_file_"$list_No".txt
	echo "Release=\""$Release"\"" 																						>> "$log_directory"/config_file_"$list_No".txt
	echo "Release_local_path=\""$Release_local_path"\"" 																>> "$log_directory"/config_file_"$list_No".txt
	echo "Analyzer=\""$Analyzer"\"" 																					>> "$log_directory"/config_file_"$list_No".txt
	echo "Architecture=\""$Architecture"\"" 																			>> "$log_directory"/config_file_"$list_No".txt
	echo "list_No=\""$list_No"\"" 																						>> "$log_directory"/config_file_"$list_No".txt

	
