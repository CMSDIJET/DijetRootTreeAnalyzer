#!/bin/bash

#./run_writeDatacards.sh 1 13 

bin_No=$1
bin_No_final=$2

Suu_masses=(8600)

alpha_true_values=(0.25)

for element1 in "${Suu_masses[@]}"
do
   for element2 in "${alpha_true_values[@]}"
   do
   
   	Suu=$element1
   	alpha_true=$element2
   	Chi=$(echo "scale=0; ($Suu*$alpha_true)/1" | bc  )   
   	echo $Suu
   	echo $Chi
   
   
        if [ $Suu == 8600 ] && [ $Chi == 2150 ]  # ref xsec = 3.3973e-05 pb 
	then
		fraction_array=(1.38573e-07	2.41872e-07	4.48472e-07	4.86264e-07	6.57591e-07	9.70009e-07	2.91255e-06	8.76032e-06	6.15767e-06	4.13451e-06	3.45424e-06	2.89491e-06	2.71603e-06 ) 
	fi


    	bin_No=1 # re-initialize alphabin counter!

	while (( $bin_No < $bin_No_final +1 ))
	do	
		fraction=${fraction_array[$bin_No-1]}
		echo $fraction	


            	python3 python/WriteDataCard_4jets_envelope.py -b PFDijetRun2_4J_alphabin$bin_No -c config/Configfiles_13_slices_envelope_3func/run2_fourjet_alpha"$bin_No"_multipdf_3_func_upto10072.config -m W-0p05_Suu --model2 Chi --mass $Suu --mass2 $Chi /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/data_histos/HISTOS_4J_AlldataRun2_SR_alphabin"$bin_No".root /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha0p25/ResonanceShapes_NOMINAL_Suu-Diquark_W-0p05_S-"$Suu"_chi-"$Chi"_alphabin"$bin_No".root --jesUp /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha0p25/ResonanceShapes_JESup_Suu-Diquark_W-0p05_S-"$Suu"_chi-"$Chi"_alphabin"$bin_No".root --jesDown /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha0p25/ResonanceShapes_JESdown_Suu-Diquark_W-0p05_S-"$Suu"_chi-"$Chi"_alphabin"$bin_No".root --jerUp /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha0p25/ResonanceShapes_JERup_Suu-Diquark_W-0p05_S-"$Suu"_chi-"$Chi"_alphabin"$bin_No".root --jerDown /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha0p25/ResonanceShapes_NOMINAL_Suu-Diquark_W-0p05_S-"$Suu"_chi-"$Chi"_alphabin"$bin_No".root -d output/Wide_Resonances_Run2_Final/datacards_alpha0p25_refxsecEqualToExpLimit/ --xsec $fraction --lumi 137600 --multi


	
	    	bin_No=$(( bin_No+1 ))
		     

		
		
	done

    	unset fraction_array


   done	
done


