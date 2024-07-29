
# Run in the folder where the datacards are stored!

bin_No=$1
bin_No_final=$2

#all
#Suu_masses=(2000 2100 2200 2300 2400 2500 2600 2700 2800 2900 3000 3100 3200 3300 3400 3500 3600 3700 3800 3900 4000 4100 4200 4300 4400 4500 4600 4700 4800 4900 5000 5100 5200 5300 5400 5500 5600 5700 5800 5900 6000 6100 6200 6300 6400 6500 6600 6700 6800 6900 7000 7100 7200 7300 7400 7500 7600 7700 7800 7900 8000 8100 8200 8300 8400 8500 8600 8700 8800 8900 9000 9100 9200 9300 9400 9500 9600 9700 9800 9900 10000)

#interpolated
Suu_masses=(2100 2200 2300 2400 2500 2600 2700 2800 2900 3100 3200 3300 3400 3500 3600 3700 3800 3900 4100 4200 4300 4400 4500 4600 4700 4800 4900 5100 5200 5300 5400 5500 5600 5700 5800 5900 6100 6200 6300 6400 6500 6600 6700 6800 6900 7100 7200 7300 7400 7500 7600 7700 7800 7900 8100 8200 8300 8500 8700 8800 8900 9100 9200 9300 9400 9500 9600 9700 9800 9900)

#simulated
#Suu_masses=(2000 3000 4000 5000 6000 7000 8000 8400 8600 9000 10000)

alpha_true_values=(0.25)

cd output/Wide_Resonances_Run2_Final/datacards_alpha0p25_refxsec0p01pb/

for element1 in "${Suu_masses[@]}"
do
   for element2 in "${alpha_true_values[@]}"
   do
   
   	Suu=$element1
   	alpha_true=$element2
   	Chi=$(echo "scale=0; ($Suu*$alpha_true)/1" | bc  )   
   	echo $Suu
   	echo $Chi
  


    	bin_No=2 # re-initialize alphabin counter! - Don's start from alphabin2, since we have to keep pdf index in alphabin1

	while (( $bin_No < $bin_No_final +1 ))
	do		
		
		sed -i 's/pdf_index/ /g' dijet_combine_W-0p1_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin"$bin_No".txt
        	sed -i 's/discrete/ /g'  dijet_combine_W-0p1_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin"$bin_No".txt
	   	sed -i '$ d' dijet_combine_W-0p1_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin"$bin_No".txt
		
		bin_No=$(( bin_No+1 ))
		
	done



   	combineCards.py   dijet_combine_W-0p1_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin1.txt dijet_combine_W-0p1_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin2.txt dijet_combine_W-0p1_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin3.txt dijet_combine_W-0p1_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin4.txt dijet_combine_W-0p1_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin5.txt dijet_combine_W-0p1_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin6.txt dijet_combine_W-0p1_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin7.txt dijet_combine_W-0p1_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin8.txt dijet_combine_W-0p1_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin9.txt dijet_combine_W-0p1_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin10.txt dijet_combine_W-0p1_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin11.txt dijet_combine_W-0p1_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin12.txt dijet_combine_W-0p1_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin13.txt >  card_combined_W-0p1_"$Suu"_"$Chi".txt

	
   done   
done
