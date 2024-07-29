#!/bin/bash

#./run_writeDatacards.sh 1 13 

bin_No=$1
bin_No_final=$2

Suu_masses=(2000 2200 3000 4000 5000 6000 7000 8000 8600 9000 10000)

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
   
   
	if [[ $Suu == 2000 ]] && [[ $Chi == 500 ]]
	then
		fraction_array=(2.36996e-05 6.48622e-05 9.79169e-05 0.000121617 0.000206436 0.000441562 0.00155482 0.00515093 0.00141387 0.00045154 0.000245104 0.000142198 8.54434e-05 )
	fi
	if [[ $Suu == 3000 ]] && [[ $Chi == 750 ]]
	then
		fraction_array=(2.81468e-05 6.41747e-05 8.66922e-05 0.000134542 0.000192524 0.000409818 0.00154019 0.00540194 0.00129363 0.000457667 0.000197028 0.00011315 8.04999e-05 )
	fi
	if [[ $Suu == 4000 ]] && [[ $Chi == 1000 ]]
	then
		fraction_array=(3.69737e-05 4.96661e-05 8.71917e-05 0.000105403 0.000213564 0.000368633 0.00154958 0.00546052 0.00133712 0.000408366 0.000198113 0.000111473 7.33955e-05 )
	fi
	if [[ $Suu == 6000 ]] && [[ $Chi == 1500 ]]
	then
		fraction_array=(3.05041e-05 5.45863e-05 7.81334e-05 0.000108637 0.000142888 0.000339291 0.00147276 0.00573103 0.00128706 0.000398694 0.000177673 0.000113454 6.52895e-05 )
	fi
	if [[ $Suu == 7000 ]] && [[ $Chi == 1750 ]]
	then
		fraction_array=(3.16506e-05 5.32785e-05 6.85763e-05 9.38967e-05 0.000154033 0.000304373 0.00138682 0.00575091 0.00132774 0.000441526 0.000186738 0.000124492 7.59614e-05 )
	fi
	if [[ $Suu == 8000 ]] && [[ $Chi == 2000 ]]
	then
		fraction_array=(2.98315e-05 4.91343e-05 7.25316e-05 0.000101778 0.000149158 0.00030475 0.00140325 0.00549953 0.00139272 0.000473795 0.000246256 0.000160856 0.000116401 )
	fi
	if [[ $Suu == 9000 ]] && [[ $Chi == 2250 ]]
	then
		fraction_array=(4.09405e-05 5.79015e-05 8.30506e-05 0.000112879 0.000156159 0.000312317 0.00129606 0.00505264 0.00143233 0.000548602 0.000363785 0.000291847 0.000251491 )
	fi
	if [[ $Suu > 2000 ]] && [[ $Suu < 3000 ]]
	then
		fraction_array=(2.59232e-05 6.45185e-05 9.23046e-05 0.000128079 0.00019948 0.00042569 0.00154751 0.00527643 0.00135375 0.000454604 0.000221066 0.000127674 8.29717e-05 )
	fi
	if [[ $Suu > 3000 ]] && [[ $Suu < 4000 ]]
	then
		fraction_array=(3.25602e-05 5.69204e-05 8.69419e-05 0.000119972 0.000203044 0.000389225 0.00154489 0.00543123 0.00131538 0.000433017 0.00019757 0.000112312 7.69477e-05 )
	fi
	if [[ $Suu > 6000 ]] && [[ $Suu < 7000 ]]
	then
		fraction_array=(3.10773e-05 5.39324e-05 7.33548e-05 0.000101267 0.00014846 0.000321832 0.00142979 0.00574097 0.0013074 0.00042011 0.000182206 0.000118973 7.06255e-05 )
	fi
	if [[ $Suu > 7000 ]] && [[ $Suu < 8000 ]]
	then
		fraction_array=(3.07411e-05 5.12064e-05 7.05539e-05 9.78375e-05 0.000151595 0.000304561 0.00139504 0.00562522 0.00136023 0.00045766 0.000216497 0.000142674 9.61814e-05 )
	fi
	if [[ $Suu > 8000 ]] && [[ $Suu < 9000 ]]
	then
		fraction_array=(3.5386e-05 5.35179e-05 7.77911e-05 0.000107328 0.000152658 0.000308533 0.00134966 0.00527608 0.00141253 0.000511199 0.000305021 0.000226352 0.000183946 )
	fi
	if [[ $Suu > 9000 ]] #same as 9000
	then
		fraction_array=(4.09405e-05 5.79015e-05 8.30506e-05 0.000112879 0.000156159 0.000312317 0.00129606 0.00505264 0.00143233 0.000548602 0.000363785 0.000291847 0.000251491 )
	fi
	if [[ $Suu > 4000 ]] && [[ $Suu < 6000 ]]
	then
		fraction_array=(3.37389e-05 5.21262e-05 8.26625e-05 0.00010702 0.000178226 0.000353962 0.00151117 0.00559577 0.00131209 0.00040353 0.000187893 0.000112463 6.93425e-05 )
	fi


	if [[ $Suu == 10000 ]] && [[ $Chi == 2500 ]]
	then
		fraction_array=(4.09405e-05 5.79015e-05 8.30506e-05 0.000112879 0.000156159 0.000312317 0.00129606 0.00505264 0.00143233 0.000548602 0.000363785 0.000291847 0.000251491 )
	fi



    	bin_No=1 # re-initialize alphabin counter!

	while (( $bin_No < $bin_No_final +1 ))
	do	
		fraction=${fraction_array[$bin_No-1]}
		echo $fraction	


            	python3 python/WriteDataCard_4jets_envelope.py -b PFDijetRun2_4J_alphabin$bin_No -c config/Configfiles_13_slices_envelope_3func/run2_fourjet_alpha"$bin_No"_multipdf_3_func_upto10072.config -m W-0p0043_Suu --model2 Chi --mass $Suu --mass2 $Chi /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/data_histos/HISTOS_4J_AlldataRun2_SR_alphabin"$bin_No".root /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/signals_13bins/alpha0p25/nominal/ResonanceShapes_Suu"$Suu"_Chi"$Chi"_SR_alphabin"$bin_No".root --jesUp /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/signals_13bins/alpha0p25/jes_up/ResonanceShapes_Suu"$Suu"_Chi"$Chi"_SR_alphabin"$bin_No".root --jesDown /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/signals_13bins/alpha0p25/jes_down/ResonanceShapes_Suu"$Suu"_Chi"$Chi"_SR_alphabin"$bin_No".root --jerUp /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/signals_13bins/alpha0p25/jer_up/ResonanceShapes_Suu"$Suu"_Chi"$Chi"_SR_alphabin"$bin_No".root --jerDown /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/signals_13bins/alpha0p25/nominal/ResonanceShapes_Suu"$Suu"_Chi"$Chi"_SR_alphabin"$bin_No".root -d output/Wide_Resonances_Run2_Final/datacards_alpha0p25_refxsec0p01pb/ --xsec $fraction --lumi 137600 --multi


	
	    	bin_No=$(( bin_No+1 ))
		     

		
		
	done

    	unset fraction_array


   done	
done


