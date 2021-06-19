#!/bin/bash

lumi=137500      #lumi in pb^-1
lumifb=137.500   #lumi in fb^-1
lumin="137.500"  #string of lumi in fb^-1

fit_start=2700
fit_end=8700

config_file="dijet.config_merged_final"
data_input="inputs/Double_sideband_inputs_16AugV11_17v6_18v10_SR_Scale.root"

box="PFDijet2017MC"
boxCRmid="PFDijet2017MCCRmid"
boxCRhigh="PFDijet2017MCCR"

xsec=0.01
xsecCRmid=0.0027
xsecCRhigh=0.0045

output_dir="deleteme/"
shapes_directory="inputs/Narrow_resonances/"

main_path=$(pwd)
resonance_type=(qq qg gg)
step=100
index=0

while (( $index <= 2 ))
do
	resonance=${resonance_type[$index]}

	directory="$output_dir/Narrow_"$resonance"_limits/"
	directory_signif="$output_dir/Narrow_"$resonance"_significance/"

	input_shape="$shapes_directory/$resonance/ResonanceShapes_"$resonance"_13TeV_Spring16.root" 
	input_shape_JERUP="$shapes_directory/$resonance/ResonanceShapes_"$resonance"_13TeV_Spring16_JERUP.root"
	input_shape_JESUP="$shapes_directory/$resonance/ResonanceShapes_"$resonance"_13TeV_Spring16_JESUP.root"
	input_shape_JESDOWN="$shapes_directory/$resonance/ResonanceShapes_"$resonance"_13TeV_Spring16_JESDOWN.root"

	echo 'mkdir '$directory 
	mkdir "$directory"
	echo 'mkdir '$directory_signif 
	mkdir "$directory_signif"

	echo '                                                                                           '
	echo '                                                                                           '
	n=$fit_start
	while (( $n <= $fit_end ))
	do
		echo '														'
		echo 'Creating datacards for SR for mass '$n'GeV...'
		set -x
		python python/WriteDataCard_simultaneous_fit_diff_param_names.py -b "$box" -c config/"$config_file"  -m "$resonance" --mass $n "$data_input" "$input_shape" --jesUp "$input_shape_JESUP" --jesDown "$input_shape_JESDOWN" --jerUp "$input_shape_JERUP"  --mc "$data_input" -d "$directory" --xsec "$xsec" --lumi $lumi --use-rooparametrichist;
		set +x

		echo '														'
		echo 'Creating datacards for CR-middle for mass '$n'GeV...'			
		set -x	
		python python/WriteDataCard_simultaneous_fit_diff_param_names.py -b "$boxCRmid" -c config/"$config_file"  -m "$resonance" --mass $n "$data_input" "$input_shape" --jesUp "$input_shape_JESUP" --jesDown "$input_shape_JESDOWN" --jerUp "$input_shape_JERUP"  --mc "$data_input" -d "$directory" --xsec "$xsecCRmid" --lumi $lumi --use-rooparametrichist;
		set +x

		echo '														'
		echo 'Creating datacards for CR-high for mass '$n'GeV...'
		set -x
		python python/WriteDataCard_simultaneous_fit_diff_param_names.py -b "$boxCRhigh" -c config/"$config_file"  -m "$resonance" --mass $n "$data_input" "$input_shape" --jesUp "$input_shape_JESUP" --jesDown "$input_shape_JESDOWN" --jerUp "$input_shape_JERUP"  --mc "$data_input" -d "$directory" --xsec "$xsecCRhigh" --lumi $lumi --use-rooparametrichist;
		set +x

		echo '														'
		echo 'Combining datacards for SR, CRmiddle, CRhigh for mass '$n'GeV...'
		set -x
		cd "$directory"
		combineCards.py "$box"=dijet_combine_"$resonance"_"$n"_lumi-"$lumin"_"$box".txt "$boxCRmid"=dijet_combine_"$resonance"_"$n"_lumi-"$lumin"_"$boxCRmid".txt "$boxCRhigh"=dijet_combine_"$resonance"_"$n"_lumi-"$lumin"_"$boxCRhigh".txt > dijet_combine_"$resonance"_"$n"_lumi-"$lumin"_"$box"_"$boxCRhigh"_"$boxCRmid".txt
		set +x

		echo '										'
		echo 'Calculating significance using the combined datacard for mass '$n'GeV...'
		set -x
		cd "$main_path"
		combine -M ProfileLikelihood --signif "$directory"/dijet_combine_"$resonance"_"$n"_lumi-"$lumin"_"$box"_"$boxCRhigh"_"$boxCRmid".txt -n "$resonance"_"$n"_lumi-"$lumin"_"$box" --rMax 200
		set +x

		echo '														'
		echo 'Calculating limits using the combined datacard for mass '$n'GeV...'
		set -x
		combine -M Asymptotic "$directory"/dijet_combine_"$resonance"_"$n"_lumi-"$lumin"_"$box"_"$boxCRhigh"_"$boxCRmid".txt -n "$resonance"_"$n"_lumi-"$lumin"_"$box" --saveWorkspace --rMax 150  #--freezeParameters=slope,beta,jes,jer,lumi,epsilon # -v3
		set +x

		echo '														'
		set -x
		mv higgsCombine"$resonance"_"$n"_lumi-"$lumin"_"$box".ProfileLikelihood.mH120.root "$directory_signif"/.;
		mv higgsCombine"$resonance"_"$n"_lumi-"$lumin"_"$box".Asymptotic.mH120.root "$directory"/.;
		set +x
		
		n=$(( n+$step ))
	done

		echo '														'
		echo '														'
		set -x
		python python/GetCombine.py --signif -d "$directory_signif" -m "$resonance" --mass range\($fit_start,$((fit_end+$step)),$step\) -b "$box" --xsec $xsec -l $lumifb
		set +x

		echo '														'
		echo '														'
		set -x
		python python/GetCombine.py -d "$directory" -m "$resonance" --mass range\($fit_start,$((fit_end+$step)),$step\) -b "$box" --xsec $xsec -l $lumifb
		set +x
		
		set -x
		python python/Plot1DLimit_deta1p1.py --signif -d "$directory_signif" -m "$resonance" -b "$box" -l $lumifb --massMin $fit_start --massMax $fit_end 
		set +x

		set -x	
		python python/Plot1DLimit_deta1p1.py -d "$directory" -m "$resonance" -b "$box" -l $lumifb --massMin $fit_start --massMax $fit_end --xsecMin 1e-5 --xsecMax 1e5
		set +x
	                                                                              
		index=$((index+1))
done
 

