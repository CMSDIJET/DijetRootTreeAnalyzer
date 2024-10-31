

#widths=('0p0043')
#widths=('0p015')
#widths=('0p05')
#widths=('0p1')
widths=('0p0043' '0p015' '0p05' '0p1')
#Suu_masses=(2200 3000 4000 5000 6000 7000 8000 8600 9000 10000)
Suu_masses=(7000)
alpha_true_values=(0.25)

for element1 in "${widths[@]}"
do
    for element2 in "${Suu_masses[@]}"
    do
        for element3 in "${alpha_true_values[@]}"
   	do

      	    width=$element1
      	    Suu=$element2
      	    alpha_true=$element3
   	    Chi=$(echo "scale=0; ($Suu*$alpha_true)/1" | bc  ) 
   	    alphap=$(echo "scale=0; ($alpha_true*100)/1" | bc  )   
   			
   	    echo $width
   	    echo $Suu
   	    echo $Chi
   	    
   	    
   	    if (( $Suu==2000 || $Suu==2200 || $Suu==3000))  
   	    then 
   	        rmin=-0.498
   	        rmax=1.502
   	    elif (( $Suu==4000 ))
   	    then
   	        rmin=-0.0498
   	        rmax=0.1502 
   	    elif (( $Suu==5000 ))
   	    then
   	        rmin=-0.00498
   	        rmax=0.01502        
   	    elif (( $Suu==8000 || $Suu==8600 || $Suu==9000 || $Suu==10000))
   	    then
   	        rmin=-0.00249
   	        rmax=0.00751
   	    elif (( $Suu==6000 ))
   	    then
   	        rmin=-0.006972
   	        rmax=0.021028
   	    elif (( $Suu==7000 ))
   	    then
   	        rmin=-0.07968
   	        rmax=0.24032        
   	    fi    
   	    
   	    
   	    screen -S list_W-"$width"_"$Suu"_"$Chi" -dm bash -c "
	        sleep 5; 
	        cmsenv;
   	        echo \"combine -M MultiDimFit output/Wide_Resonances_Run2_Final/datacards_alpha0p"$alphap"_refxsec0p01pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt --rMin $rmin --rMax $rmax --algo grid --points 500 --cminDefaultMinimizerStrategy 0 --saveNLL --X-rtd REMOVE_CONSTANT_ZERO_POINT=1 --robustFit 1 --trackParameters rgx{.*} --saveSpecifiedIndex pdf_index -n _envelope_W-"$width"_"$Suu"_"$Chi"\";   	    
                combine -M MultiDimFit output/Wide_Resonances_Run2_Final/datacards_alpha0p"$alphap"_refxsec0p01pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt --rMin $rmin --rMax $rmax --algo grid --points 500 --cminDefaultMinimizerStrategy 0 --saveNLL --X-rtd REMOVE_CONSTANT_ZERO_POINT=1 --robustFit 1 --trackParameters rgx{.*} --saveSpecifiedIndex pdf_index -n _envelope_W-"$width"_"$Suu"_"$Chi";
	        mv higgsCombine_envelope_W-"$width"_"$Suu"_"$Chi".MultiDimFit.mH120.root output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/dnlls/;
                exec bash"
        done
	
   done   
done
