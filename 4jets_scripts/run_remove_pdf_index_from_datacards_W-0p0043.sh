
# Run in the folder where the datacards are stored!

bin_No=$1
bin_No_final=$2

Suu_masses=(2000 2200 3000 4000 5000 6000 7000 8000 8600 9000 10000)

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
		
		sed -i 's/pdf_index/ /g' dijet_combine_W-0p0043_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin"$bin_No".txt
        	sed -i 's/discrete/ /g'  dijet_combine_W-0p0043_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin"$bin_No".txt
	   	sed -i '$ d' dijet_combine_W-0p0043_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin"$bin_No".txt
		
		bin_No=$(( bin_No+1 ))
		
	done



   	combineCards.py   dijet_combine_W-0p0043_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin1.txt dijet_combine_W-0p0043_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin2.txt dijet_combine_W-0p0043_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin3.txt dijet_combine_W-0p0043_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin4.txt dijet_combine_W-0p0043_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin5.txt dijet_combine_W-0p0043_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin6.txt dijet_combine_W-0p0043_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin7.txt dijet_combine_W-0p0043_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin8.txt dijet_combine_W-0p0043_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin9.txt dijet_combine_W-0p0043_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin10.txt dijet_combine_W-0p0043_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin11.txt dijet_combine_W-0p0043_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin12.txt dijet_combine_W-0p0043_Suu_Chi_"$Suu"_"$Chi"_lumi-137.600_PFDijetRun2_4J_alphabin13.txt >  card_combined_W-0p0043_"$Suu"_"$Chi".txt

	
   done   
done
