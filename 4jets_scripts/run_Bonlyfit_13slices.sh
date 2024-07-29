#!/bin/bash

# ./run_Bonlyfit.sh 1 13

bin_No=$1
bin_No_final=$2
	

	while (( $bin_No < $bin_No_final +1 ))
	do
		python python/BinnedFit_4jets.py -c config/Configfiles_13_slices_moddijet_only/run2_fourjet_alpha"$bin_No"_moddijet_only_upto10072GeV.config -l 275200 inputs/run2/pseudodata_CMSRunIIPlusBkgToyPlusATLASEvent/HISTOS_4J_CMSRunIIPlusBkgToyPlusATLASEvent_SR_alphabin"$bin_No".root -b PFDijetRun2_4J_alphabin"$bin_No" -d output/Wide_Resonances_CMSRunIIPlusBkgToyPlusATLASEvent/BkgOnlyFits/Moddijet-3p/ --fit-spectrum 
		bin_No=$(( bin_No+1 ))
	done


