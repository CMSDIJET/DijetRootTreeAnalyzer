
widths=('0p0043' '0p015' '0p05' '0p1')
Suu_masses=(2000 2200 3000 4000 5000 6000 7000 8000 8600 9000 10000)
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

            if [ "$width" == '0p0043' ]; then
                if [ $Suu -lt 3500 ]
                then
                    rmax=5
                elif [ $Suu -lt 5000 ]
                then
                    rmax=1   
                elif [ $Suu -lt 5500 ] 
                then 
                    rmax=0.1
                elif [ $Suu -lt 6000 ] 
                then
                    rmax=0.08
                elif [ $Suu -lt 6500 ] 
                then
                    rmax=0.05
                elif [ $Suu -lt 7000 ] 
                then
                    rmax=0.04
                elif [ $Suu -lt 7500 ] 
                then
                    rmax=0.03
                elif [ $Suu -lt 8000 ] 
                then
                    rmax=0.02
                else
                    rmax=0.02
                fi
          else  
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
            if (( $Suu>=9000 && $Suu < 10000 )); then rmax=0.055; fi
         fi   
	    
	 screen -S list_W-"$width"_"$Suu"_"$Chi" -dm bash -c "
	        sleep 5; 
	        cmsenv;   
	        echo \"combine -M FitDiagnostics output/Wide_Resonances_Run2_Final/datacards_alpha0p"$alphap"_refxsec0p01pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt --robustFit 1 --rMin 0 --rMax "$rmax" --setCrossingTolerance 0.00001 --cminDefaultMinimizerStrategy=0 -n _W-"$width"_"$Suu"_"$Chi"\";	   
	        combine -M FitDiagnostics output/Wide_Resonances_Run2_Final/datacards_alpha0p"$alphap"_refxsec0p01pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt --robustFit 1 --rMin 0 --rMax "$rmax" --setCrossingTolerance 0.00001 --cminDefaultMinimizerStrategy=0 -n _W-"$width"_"$Suu"_"$Chi";
	        mv fitDiagnostics_W-"$width"_"$Suu"_"$Chi".root output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/fit_diagnostics/;
	        mv higgsCombine_W-"$width"_"$Suu"_"$Chi".FitDiagnostics.mH120.root output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/fit_diagnostics/;
	        exec bash"
       
       done
   done
done

