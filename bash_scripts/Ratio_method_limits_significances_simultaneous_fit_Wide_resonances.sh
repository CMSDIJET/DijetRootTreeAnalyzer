#!/bin/bash

width_percentage=(01 05 1 15 2 25 3 35 4 45 5 55)



data_input="inputs/Double_sideband_inputs_16AugV11_17v6_18v10_SR_Scale.root"


signal_type="Spin1"
#signal_type="Spin1"


fit_start=2700
fit_end=8100
step=100

lumi=137500      #lumi in pb^-1
lumifb=137.500   #lumi in fb^-1
lumin="137.500"  #string of lumi in fb^-1


box="PFDijet2017MC"
boxCRmid="PFDijet2017MCCRmid"
boxCRhigh="PFDijet2017MCCR"

config_file="config/dijet.config_merged_final"

xsec=0.01
xsecCRmid=0.0027
xsecCRhigh=0.0045


resonance="gg"

output_dir_limits="EXO_19-012/Wide_resonances/limits"
output_dir_signif="EXO_19-012/Wide_resonances/signif"

if [[ "$signal_type" == "Spin1" ]]; then
	shapes_directory="inputs/Spin1_WideResonance_shapes/"
	max_width=11
	resonance="qq"
	echo "Spin 1, $resonance has been selected." 
elif [[ "$signal_type" == "Spin2" ]]; then
	shapes_directory="inputs/Spin2_WideResonance_shapes/$resonance/"
	max_width=6
	echo "Spin 2, $resonance has been selected." 
fi

main_path=$(pwd)

mkdir "$output_dir_limits"
mkdir "$output_dir_signif"
index=0

while (( $index <= $max_width ))
do
#for spin1 resonances with width >=10% the fit is performed up to 6000
	if [ "$signal_type" == "Spin1" ] &&  [ $index -ge 2 ]
	then 
		fit_end=6000
	fi
	echo "$fit_end"
	m=${width_percentage[$index]}

	directory="$output_dir_limits/"$resonance"_0p$m"
	directory_signif="$output_dir_signif/"$resonance"_0p$m"

	echo '                                                                                           '
	mkdir "$directory"


#	echo 'mkdir '$directory_signif 
	mkdir "$directory_signif"
	echo '                                                                                           '
	echo '                           																 '


	input_shape="$shapes_directory/ResonanceShapes_"$resonance"_13TeV_Spring16_W-0p"$m".root" #spin1 shapes new JER

	input_shape_JERUP="$shapes_directory/ResonanceShapes_"$resonance"_13TeV_Spring16_JERUP_W-0p"$m".root"
	input_shape_JESUP="$shapes_directory/ResonanceShapes_"$resonance"_13TeV_Spring16_JESUP_W-0p"$m".root"
	input_shape_JESDOWN="$shapes_directory/ResonanceShapes_"$resonance"_13TeV_Spring16_JESDOWN_W-0p"$m".root"



	n=$fit_start


	while (( $n <= $fit_end ))
	do

		echo 'Creating datacards for SR for mass '$n'GeV...'
		echo ''
		echo '                                                                                           '

		set -x	#this will print the following commands on terminal
		python python/WriteDataCard_simultaneous_fit_diff_param_names.py -b "$box" -c "$config_file"  -m "$resonance" --mass $n "$data_input" "$input_shape" --jesUp "$input_shape_JESUP" --jesDown "$input_shape_JESDOWN" --jerUp "$input_shape_JERUP" --mc "$data_input" -d "$directory" --xsec "$xsec" --lumi $lumi --use-rooparametrichist ;
		set +x	#this will stop printing the following commands on terminal

		echo '                                                                                           '	
		echo 'Creating datacards for CR middle for mass '$n'GeV...'
		echo ''
		echo '                                                                                           '
		set -x	
		python python/WriteDataCard_simultaneous_fit_diff_param_names.py -b "$boxCRmid" -c "$config_file"  -m "$resonance" --mass $n "$data_input" "$input_shape" --jesUp "$input_shape_JESUP" --jesDown "$input_shape_JESDOWN" --jerUp "$input_shape_JERUP" --mc "$data_input" -d "$directory" --xsec "$xsecCRmid" --lumi $lumi --use-rooparametrichist;
		set +x

		echo '                                                                                           '	
		echo 'Creating datacards for CR high for mass '$n'GeV...'
		echo ''
		echo '                                                                                           '		
		set -x
		python python/WriteDataCard_simultaneous_fit_diff_param_names.py -b "$boxCRhigh" -c "$config_file"  -m "$resonance" --mass $n "$data_input" "$input_shape" --jesUp "$input_shape_JESUP" --jesDown "$input_shape_JESDOWN" --jerUp "$input_shape_JERUP" --mc "$data_input" -d "$directory" --xsec "$xsecCRhigh" --lumi $lumi --use-rooparametrichist;

	
		cd "$directory"
		set +x
		echo '														'
		echo 'Combining datacards for SR, CRmiddle, CRhigh for mass '$n' GeV...'
		echo ''

		set -x
		combineCards.py "$box"=dijet_combine_"$resonance"_"$n"_lumi-"$lumin"_"$box".txt "$boxCRmid"=dijet_combine_"$resonance"_"$n"_lumi-"$lumin"_"$boxCRmid".txt "$boxCRhigh"=dijet_combine_"$resonance"_"$n"_lumi-"$lumin"_"$boxCRhigh".txt > dijet_combine_"$resonance"_"$n"_lumi-"$lumin"_"$box"_"$boxCRhigh"_"$boxCRmid".txt
		cd "$main_path"
		set +x

		echo 'Calculating limits & significanses using the combined datacard for mass '$n'GeV...'
		echo ''
		set -x		
		combine -M Asymptotic "$directory"/dijet_combine_"$resonance"_"$n"_lumi-"$lumin"_"$box"_"$boxCRhigh"_"$boxCRmid".txt -n "$resonance"_"$n"_lumi-"$lumin"_"$box" --saveWorkspace --rMax 50 #--freezeParameters=jes_2017,jer_2017 #-v3
		combine -M ProfileLikelihood --signif "$directory"/dijet_combine_"$resonance"_"$n"_lumi-"$lumin"_"$box"_"$boxCRhigh"_"$boxCRmid".txt -n "$resonance"_"$n"_lumi-"$lumin"_"$box" --rMax 100 #--freezeParameters=slope,beta,jes,jer,lumi,epsilon

		mv higgsCombine"$resonance"_"$n"_lumi-"$lumin"_"$box".Asymptotic.mH120.root "$directory"/.;
		mv higgsCombine"$resonance"_"$n"_lumi-"$lumin"_"$box".ProfileLikelihood.mH120.root "$directory_signif"/.;

		set +x
		echo '														'

		n=$(( n+$step ))
	done

	echo '														'
	echo '														'



	set -x
	python python/GetCombine.py --signif -d "$directory_signif" -m "$resonance" --mass range\($fit_start,$((fit_end+$step)),$step\) -b "$box" --xsec $xsec -l $lumifb
	set +x


	echo '                                                                                           '
	echo '                                                                                           '

	set -x
	python python/GetCombine.py -d "$directory" -m "$resonance" --mass range\($fit_start,$((fit_end+$step)),$step\) -b "$box" --xsec "$xsec" -l $lumifb
	set +x


	echo '                                                                                           '
	echo '                                                                                           '	
	


		
	set -x
	python python/Plot1DLimit_deta1p1_Wide.py --signif -d "$directory_signif" -m "$resonance" -b "$box" -l $lumifb --massMin $fit_start --massMax $fit_end 
	python python/Plot1DLimit_deta1p1_Wide.py -d "$directory" -m "$resonance" -b "$box" -l $lumifb --massMin $fit_start --massMax $fit_end --xsecMin 1e-5 --xsecMax 1e2
	set +x

	echo '														'
	

 index=$((index+1))
done

