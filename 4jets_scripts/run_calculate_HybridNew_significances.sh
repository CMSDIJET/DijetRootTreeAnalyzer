
widths=('0p015')
Suu_masses=(7000 7100 7200 7300 7400 7500 7600 7700 7800 7900 8000 8100 8200 8300 8400 8500 8600 8700 8800 8900 9000 9100 9200 9300 9400 9500 9600 9700 9800 9900 10000)
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
  
            source /cvmfs/cms.cern.ch/crab3/crab.sh 
            eval `scramv1 runtime -sh` #equivalent to cmsenv
            
                        
            if [ "$width" == '0p015' ] 
            then
                if (( $Suu>=4500 && $Suu < 5000 ));   then max=0.0380; fi
                if (( $Suu>=5000 && $Suu < 5500 ));   then max=0.0240; fi
                if (( $Suu>=5500 && $Suu < 6000 ));   then max=0.0170; fi
                if (( $Suu>=6000 && $Suu < 6500 ));   then max=0.0130; fi
                if (( $Suu>=6500 && $Suu < 7000 ));   then max=0.0100; fi
                if (( $Suu>=7000 && $Suu < 8000 ));   then max=0.0080; fi
                if (( $Suu>=8000 && $Suu < 9000 ));   then max=0.0070; fi
                if (( $Suu>=9000 && $Suu <= 10000 )); then max=0.0085; fi
            elif [ "$width" == '0p05' ]
            then 
                if (( $Suu>=4500 && $Suu < 5000 ));   then max=0.0500; fi
                if (( $Suu>=5000 && $Suu < 5500 ));   then max=0.0300; fi
                if (( $Suu>=5500 && $Suu < 6000 ));   then max=0.0220; fi
                if (( $Suu>=6000 && $Suu < 6500 ));   then max=0.0150; fi
                if (( $Suu>=6500 && $Suu < 7000 ));   then max=0.0120; fi
                if (( $Suu>=7000 && $Suu < 8000 ));   then max=0.0100; fi
                if (( $Suu>=8000 && $Suu < 9000 ));   then max=0.0085; fi
                if (( $Suu>=9000 && $Suu <= 10000 )); then max=0.0120; fi
            elif [ "$width" == '0p1' ]
            then
                if (( $Suu>=4500 && $Suu < 5000 ));   then max=0.0520; fi
                if (( $Suu>=5000 && $Suu < 5500 ));   then max=0.0330; fi
                if (( $Suu>=5500 && $Suu < 6000 ));   then max=0.0225; fi
                if (( $Suu>=6000 && $Suu < 6500 ));   then max=0.0160; fi
                if (( $Suu>=6500 && $Suu < 7000 ));   then max=0.0130; fi
                if (( $Suu>=7000 && $Suu < 8000 ));   then max=0.0115; fi
                if (( $Suu>=8000 && $Suu < 9000 ));   then max=0.0100; fi
                if (( $Suu>=9000 && $Suu <= 10000 )); then max=0.0120; fi
            fi
            
   
            rmax=$(echo "scale=3; (4*$max)/1" | bc  )

            #Run with screens	  	  	  
	    screen -S screen_Signif_W-"$width"_"$Suu"_"$Chi" -dm bash -c "
	        sleep 5; 
	        cmsenv;	        
                combine output/Wide_Resonances_Run2_Final/datacards_alpha0p"$alphap"_refxsec0p01pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt -M HybridNew --LHCmode LHC-significance --readHybridResults --toysFile=output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/HN_significances/crab_final_hybridNew_significances_13_slices_envelope_3_func_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"/results/significances_13_slices_envelope_3_func_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"_merged.root -m 120 -n Signif_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi" --signalForSignificance "$rmax" --plot significance_plot_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi";
            exec bash "    
                        
 
        done    
    done
done    
        
