#Suu_masses=(2000 2100 2200 2300 2400 2500 2600 2700 2800 2900 3000 3100 3200 3300 3400 3500 3600 3700 3800 3900 4000 4100 4200 4300 4400 4500 4600 4700 4800 4900 5000 5100 5200 5300 5400 5500 5600 5700 5800 5900 6000 6100 6200 6300 6400 6500 6600 6700 6800 6900 7000 7100 7200 7300 7400 7500 7600 7700 7800 7900 8000 8100 8200 8300 8400 8500 8600 8700 8800 8900 9000 9100 9200 9300 9400 9500 9600 9700 9800 9900 10000)
Suu_masses=(4900 6200)
widths=('0p1')
#alpha_true_values=(0.11 0.13 0.15 0.17 0.19 0.21 0.23 0.27 0.29 0.31 0.33 0.42)
alpha_true_values=(0.42)

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

	    if (( $Suu>=2000 && $Suu < 2500 ));  then rmax=6.00; fi
	    if (( $Suu>=2500 && $Suu < 3000 ));  then rmax=2.50; fi
            if (( $Suu>=3000 && $Suu < 3500 ));  then rmax=1.20; fi
            if (( $Suu>=3500 && $Suu < 4000 ));  then rmax=0.70; fi 
            if (( $Suu>=4000 && $Suu < 4500 ));  then rmax=0.50; fi
            if (( $Suu>=4500 && $Suu < 5000 ));  then rmax=0.30; fi
            if (( $Suu>=5000 && $Suu < 5500 ));  then rmax=0.20; fi
            if (( $Suu>=5500 && $Suu < 6000 ));  then rmax=0.15; fi
            if (( $Suu>=6000 && $Suu < 6500 ));  then rmax=0.08; fi
            if (( $Suu>=6500 && $Suu < 7000 ));  then rmax=0.07; fi
            if (( $Suu>=7000 && $Suu < 8000 ));  then rmax=0.06; fi
            if (( $Suu>=8000 && $Suu < 9000 ));  then rmax=0.05; fi
            if (( $Suu>=9000 && $Suu <= 10000 )); then rmax=0.055; fi
	    
	    combine -M Significance output/Wide_Resonances_Run2_Final/datacards_alpha0p"$alphap"_refxsec0p01pb/workspace_combined_W-"$width"_"$Suu"_"$Chi".root --rMin 0 --rMax "$rmax" --saveWorkspace -n _alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"

	    #mv higgsCombine_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi".Significance.mH120.root output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/asympt_significances/
       done
   done
done

