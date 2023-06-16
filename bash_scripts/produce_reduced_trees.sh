#!/bin/bash


input_config_txt=$1
Full_path_to_DijetRootTreeAnalyzer=$2
source "$Full_path_to_DijetRootTreeAnalyzer"/"$input_config_txt"

run_local=$3  # set to 1 to run locally with "Run_reduced_trees_locally.sh"

if [ $run_local -ne 1 ] ;
then
	cp -r "$Release_local_path" .
	cd "$Release"/src/
	cd CMSDIJET/DijetRootTreeAnalyzer/
fi



export SCRAM_ARCH="$Architecture"
source $VO_CMS_SW_DIR/cmsset_default.sh
eval `scramv1 runtime -sh`


echo ""
echo 'First list No: '$list_No

echo 'Output directory: '$directory



ln -sf "$Analyzer" src/analysisClass.C
make clean
make

		./main "$list_name" $cutFile dijets/events "$directory"/"$Output_base_name"_"$list_No"of10 output/cutEfficiencyFile_"$list_No"









