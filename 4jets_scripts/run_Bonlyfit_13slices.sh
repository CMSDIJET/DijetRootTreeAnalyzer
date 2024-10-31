#!/bin/bash

# ./run_Bonlyfit.sh 1 13

bin_No=$1
bin_No_final=$2
	

	while (( $bin_No < $bin_No_final +1 ))
	do
		#python3 python/BinnedFit_4jets.py -c config/Configfiles_13_slices_dijet_only_4PAR/run2_fourjet_alpha"$bin_No"_dijet_only_upto10072GeV.config -l 137600 /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/data_histos/HISTOS_4J_AlldataRun2_SR_alphabin"$bin_No".root -b PFDijetRun2_4J_alphabin"$bin_No" -d output/Wide_Resonances_Run2_4parFits/BkgFits/Dijet-4p/ --fit-spectrum 
		#python3 python/BinnedFit_4jets.py -c config/Configfiles_13_slices_atlas_only_4PAR/run2_fourjet_alpha"$bin_No"_atlas_only_upto10072GeV.config -l 137600 /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/data_histos/HISTOS_4J_AlldataRun2_SR_alphabin"$bin_No".root -b PFDijetRun2_4J_alphabin"$bin_No" -d output/Wide_Resonances_Run2_4parFits/BkgFits/PowExp-4p/ --fit-spectrum
		python3 python/BinnedFit_4jets.py -c config/Configfiles_13_slices_moddijet_only_4PAR/run2_fourjet_alpha"$bin_No"_moddijet_only_upto10072GeV.config -l 137600 /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/data_histos/HISTOS_4J_AlldataRun2_SR_alphabin"$bin_No".root -b PFDijetRun2_4J_alphabin"$bin_No" -d output/Wide_Resonances_Run2_4parFits/BkgFits/ModDijet-4p/ --fit-spectrum
		bin_No=$(( bin_No+1 ))
	done


