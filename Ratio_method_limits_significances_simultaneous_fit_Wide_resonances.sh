#!/bin/bash

width_percentage=(01 05 1 15 2 25 3 35 4 45 5 55)


#data_input="inputs/Double_sideband_inputs_2018_Autumn18_V10.root"
#data_input="inputs/Double_sideband_inputs_2017_Fall17_17Nov2017_V6.root"
#data_input="inputs/Double_sideband_inputs_2016_07Aug2017_V11.root"

data_input="inputs/Double_sideband_inputs_16AugV11_17v6_18v10_SR_Scale.root"


#data_input="inputs/Double_sideband_inputs_18_v10_merged.root"
#data_input="inputs/Double_sideband_inputs_2017_v6_merged.root"
#data_input="inputs/Double_sideband_inputs_16AugV11_merged.root"

#data_input="Double_sideband_inputs_16v11_17v6_18v10_merged.root"


fit_start=5000
fit_end=5200
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


resonance="qq"

output_dir_limits="deleteme/limits"
output_dir_signif="deleteme/signif"
shapes_directory="inputs/Spin1_WideResonance_shapes/"

main_path=$(pwd)

mkdir "$output_dir_limits"
mkdir "$output_dir_signif"
index=6
while (( $index <= 6 ))
do

	m=${width_percentage[$index]}

	directory="$output_dir_limits/"$resonance"_0p$m"

	directory_signif="$output_dir_signif/"$resonance"_0p$m"
#	shapes_directory="New_JER_implementation_Spin1/"
#	shapes_directory="LogLinear_interpolated_wide_shapes/DM_spin1/"


	echo 'mkdir '$directory
	echo '                                                                                           '
	echo '                                                                                           '
	mkdir "$directory"


	echo 'mkdir '$directory_signif 
	mkdir "$directory_signif"
	echo '                                                                                           '
	echo '                           																 '


	input_shape="$shapes_directory/ResonanceShapes_qq_13TeV_Spring16_W-0p"$m".root" #spin1 shapes new JER

	input_shape_JERUP="$shapes_directory/ResonanceShapes_qq_13TeV_Spring16_JERUP_W-0p"$m".root"
	input_shape_JESUP="$shapes_directory/ResonanceShapes_qq_13TeV_Spring16_JESUP_W-0p"$m".root"
	input_shape_JESDOWN="$shapes_directory/ResonanceShapes_qq_13TeV_Spring16_JESDOWN_W-0p"$m".root"


	


#	input_shape="inputs/"$shapes_directory"/ResonanceShapes_RSG"$resonance"_W-0p"$m"_low_stat.root" #spin2 shapes
#spin 2 uncertainties
#	input_shape_JESUP="inputs/RSG_"$resonance"_resonance_shape/ResonanceShapes_"$resonance"_13TeV_Spring16_JESUP_W-0p"$m".root"
#	input_shape_JESDOWN="inputs/RSG_"$resonance"_resonance_shape/ResonanceShapes_"$resonance"_13TeV_Spring16_JESDOWN_W-0p"$m".root"
#	input_shape_JERUP="inputs/RSG_"$resonance"_resonance_shape/ResonanceShapes_"$resonance"_13TeV_Spring16_JERUP_W-0p"$m".root"
#	input_shape_JERDOWN="inputs/RSG_"$resonance"_resonance_shape/ResonanceShapes_"$resonance"_13TeV_Spring16_JERDOWN_W-0p"$m".root"
	n=$fit_start


	while (( $n <= $fit_end ))
#	while (( $n <= 0 ))
	do

		echo 'Creating datacards for SR for mass '$n'GeV...'
		echo ''
		echo 'python/WriteDataCard_simultaneous_fit.py -b '$box' -c '$config_file'  -m '$resonance' --mass '$n' '$data_input' '$input_shape' --jesUp '$input_shape_JESUP' --jesDown '$input_shape_JESDOWN' --jerUp '$input_shape_JERUP' --mc '$data_input' -d '$directory' --xsec '$xsec' --lumi '$lumi' --use-rooparametrichist '

		echo '                                                                                           '
		echo '                                                                                           '
	
		python python/WriteDataCard_simultaneous_fit_diff_param_names.py -b "$box" -c "$config_file"  -m "$resonance" --mass $n "$data_input" "$input_shape" --jesUp "$input_shape_JESUP" --jesDown "$input_shape_JESDOWN" --jerUp "$input_shape_JERUP" --mc "$data_input" -d "$directory" --xsec "$xsec" --lumi $lumi --use-rooparametrichist ;

	
		echo '                                                                                           '	
		echo 'Creating datacards for CR middle for mass '$n'GeV...'
		echo ''
		echo 'python/WriteDataCard_simultaneous_fit.py -b '$boxCRmid' -c '$config_file'  -m '$resonance' --mass '$n' '$data_input' '$input_shape' --jesUp '$input_shape_JESUP' --jesDown '$input_shape_JESDOWN' --jerUp '$input_shape_JERUP' --mc '$data_input' -d '$directory' --xsec '$xsecCRmid' --lumi '$lumi' --use-rooparametrichist '

		echo '                                                                                           '

		python python/WriteDataCard_simultaneous_fit_diff_param_names.py -b "$boxCRmid" -c "$config_file"  -m "$resonance" --mass $n "$data_input" "$input_shape" --jesUp "$input_shape_JESUP" --jesDown "$input_shape_JESDOWN" --jerUp "$input_shape_JERUP" --mc "$data_input" -d "$directory" --xsec "$xsecCRmid" --lumi $lumi --use-rooparametrichist;

	

		echo '                                                                                           '	
		echo 'Creating datacards for CR high for mass '$n'GeV...'
		echo ''
		echo 'python/WriteDataCard_simultaneous_fit.py -b '$boxCRhigh' -c '$config_file'  -m '$resonance' --mass '$n' '$data_input' '$input_shape' --jesUp '$input_shape_JESUP' --jesDown '$input_shape_JESDOWN' --jerUp '$input_shape_JERUP' --mc '$data_input' -d '$directory' --xsec '$xsecCRhigh' --lumi '$lumi' --use-rooparametrichist '

		echo '                                                                                           '

		python python/WriteDataCard_simultaneous_fit_diff_param_names.py -b "$boxCRhigh" -c "$config_file"  -m "$resonance" --mass $n "$data_input" "$input_shape" --jesUp "$input_shape_JESUP" --jesDown "$input_shape_JESDOWN" --jerUp "$input_shape_JERUP" --mc "$data_input" -d "$directory" --xsec "$xsecCRhigh" --lumi $lumi --use-rooparametrichist;

	
		
		echo '														'

		echo 'cd '$directory

		cd "$directory"

		echo '														'
		echo 'Combining datacards for SR, CRmiddle, CRhigh for mass '$n'GeV...'
		echo ''
		echo 'combineCards.py '$box'=dijet_combine_'$resonance'_'$n'_lumi-'$lumin'_'$box'.txt '$boxCRmid'=dijet_combine_'$resonance'_'$n'_lumi-'$lumin'_'$boxCRmid'.txt '$boxCRhigh'=dijet_combine_'$resonance'_'$n'_lumi-'$lumin'_'$boxCRhigh'.txt > dijet_combine_'$resonance'_'$n'_lumi-'$lumin'_'$box'_'$boxCRhigh'_'$boxCRmid'.txt'

		combineCards.py "$box"=dijet_combine_"$resonance"_"$n"_lumi-"$lumin"_"$box".txt "$boxCRmid"=dijet_combine_"$resonance"_"$n"_lumi-"$lumin"_"$boxCRmid".txt "$boxCRhigh"=dijet_combine_"$resonance"_"$n"_lumi-"$lumin"_"$boxCRhigh".txt > dijet_combine_"$resonance"_"$n"_lumi-"$lumin"_"$box"_"$boxCRhigh"_"$boxCRmid".txt

		echo '														'

		echo 'cd $main_path'

		cd "$main_path"

		echo 'Calculating limits using the combined datacard for mass '$n'GeV...'
		echo ''
		echo 'combine -M Asymptotic '$directory'/dijet_combine_'$resonance'_'$n'_lumi-'$lumin'_'$box'_'$boxCRhigh'_'$boxCRmid'.txt -n '$resonance'_'$n'_lumi-'$lumin'_'$box' --saveWorkspace --rMax 200' #--freezeParameters=slope,beta,jes,jer,lumi,epsilon -v3'

		
		combine -M Asymptotic "$directory"/dijet_combine_"$resonance"_"$n"_lumi-"$lumin"_"$box"_"$boxCRhigh"_"$boxCRmid".txt -n "$resonance"_"$n"_lumi-"$lumin"_"$box" --saveWorkspace --rMax 50 #--freezeParameters=jes_2017,jer_2017 #-v3


		echo '														'

		echo 'combine -M ProfileLikelihood --signif '$directory'/dijet_combine_'$resonance'_'$n'_lumi-'$lumin'_'$box'_'$boxCRhigh'_'$boxCRmid'.txt -n '$resonance'_'$n'_lumi-'$lumin'_'$box' --rMax 200 '

		combine -M ProfileLikelihood --signif "$directory"/dijet_combine_"$resonance"_"$n"_lumi-"$lumin"_"$box"_"$boxCRhigh"_"$boxCRmid".txt -n "$resonance"_"$n"_lumi-"$lumin"_"$box" --rMax 100 #--freezeParameters=slope,beta,jes,jer,lumi,epsilon

		echo '														'

		echo 'mv higgsCombine'$resonance'_'$n'_lumi-'$lumin'_'$box'.Asymptotic.mH120.root '$directory'/.;'

		mv higgsCombine"$resonance"_"$n"_lumi-"$lumin"_"$box".Asymptotic.mH120.root "$directory"/.;


		echo 'mv higgsCombine'$resonance'_'$n'_lumi-'$lumin'_'$box'.ProfileLikelihood.mH120.root '$directory_signif'/.;'

		mv higgsCombine"$resonance"_"$n"_lumi-"$lumin"_"$box".ProfileLikelihood.mH120.root "$directory_signif"/.;

		echo '														'

		n=$(( n+$step ))
	done

	echo '														'
	echo '														'


	echo 'python python/GetCombine.py --signif -d '$directory_signif' -m '$resonance' --mass range\('$fit_start','$((fit_end+$step))','$step'\) -b '$box' --xsec '$xsec' -l '$lumifb	

	python python/GetCombine.py --signif -d "$directory_signif" -m "$resonance" --mass range\($fit_start,$((fit_end+$step)),$step\) -b "$box" --xsec $xsec -l $lumifb

	echo 'python python/GetCombine.py -d '$directory' -m '$resonance' --mass range\('$fit_start','$((fit_end+$step))','$step'\) -b '$box' --xsec '$xsec' -l '$lumin' '

	echo '                                                                                           '
	echo '                                                                                           '

	python python/GetCombine.py -d "$directory" -m "$resonance" --mass range\($fit_start,$((fit_end+$step)),$step\) -b "$box" --xsec "$xsec" -l $lumifb

	echo 'python python/Plot1DLimit_deta1p1.py -d '$directory' -m '$resonance' -b '$box' -l '$lumin' --massMin '$fit_start' --massMax '$fit_end' --xsecMin 1e-5 --xsecMax 1e5'

	echo '                                                                                           '
	echo '                                                                                           '	
	

	echo 'python python/Plot1DLimit_deta1p1.py --signif -d '$directory_signif' -m '$resonance' -b '$box' -l '$lumifb' --massMin '$fit_start' --massMax '$fit_end
		

#	python python/Plot1DLimit_deta1p1.py --signif -d "$directory_signif" -m "$resonance" -b "$box" -l $lumifb --massMin $fit_start --massMax $fit_end 

	echo '														'

#	python python/Plot1DLimit_deta1p1.py -d "$directory" -m "$resonance" -b "$box" -l $lumifb --massMin $fit_start --massMax $fit_end --xsecMin 1e-5 --xsecMax 1e2

	echo '														'

	echo 'Deleting intermediate unnecessary files: Datacards, higgsCombine files, etc. ' 

	echo '														'

	echo 'rm '$directory'/dijet_combine_'$resonance'_*_'$box'.txt	'

	#rm "$directory"/dijet_combine_"$resonance"_*_"$box".txt	

	echo '														'

	echo 'rm '$directory'/dijet_combine_'$resonance'_*_'$box'.root	'

	#rm "$directory"/dijet_combine_"$resonance"_*_"$box".root	

	echo '														'

	echo 'rm '$directory'/dijet_combine_'$resonance'_*_'$boxCRhigh'.txt	'

	#rm "$directory"/dijet_combine_"$resonance"_*-"$lumin"_"$boxCRhigh".txt	

	echo '														'

	echo 'rm '$directory'/dijet_combine_'$resonance'_*-'$lumin'_'$boxCRhigh'.root	'

	#rm "$directory"/dijet_combine_"$resonance"_*-"$lumin"_"$boxCRhigh".root

	echo '														'

	echo 'rm '$directory'/higgsCombine'$resonance'_*.root		'

#	rm "$directory"/higgsCombine"$resonance"_*.root	

	echo '														'

	echo 'rm '$directory'/xsecUL_'$resonance'_*_'$box'.root		'

#	rm "$directory"/xsecUL_"$resonance"_*_"$box".root		

 index=$((index+1))
done




