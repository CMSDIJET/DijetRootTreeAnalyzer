
widths=('0p1')
#Suu_masses=(4500 4600 4700 4800 4900 5000 5100 5200 5300 5400 5500 5600 5700 5800 5900 6000 6100 6200 6300 6400 6500 6600 6700 6800 6900 7000 7100 7200 7300 7400 7500 7600 7700 7800 7900 8000 8100 8200 8300 8400 8500 8600 8700 8800 8900 9000 9100 9200 9300 9400 9500 9600 9700 9800 9900 10000)
#Suu_masses=(4500 4600 4700 4800 4900 5000 5100 5200 5300 5400 5500 5600 5700 5800 5900 6000 6100 6200 6300 6400 6500 6600 6700 6800 6900 7000 7100 7200)
Suu_masses=(7300 7400 7500 7600 7700 7800 7900 8000 8100 8200 8300 8400 8500 8600 8700 8800 8900 9000 9100 9200 9300 9400 9500 9600 9700 9800 9900 10000)
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
            
   
            stepsize=$(echo "scale=7;   (0.005*$max)/1" | bc  )   #0.005 means 200 scans of signal strength

            #Run with screens	  	  	  
	    screen -S screen_W-"$width"_"$Suu"_"$Chi" -dm bash -c "
	        sleep 5; 
	        cmsenv;
	        
                combine output/Wide_Resonances_Run2_Final/datacards_alpha0p"$alphap"_refxsec0p01pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt -M HybridNew --LHCmode LHC-limits --readHybridResults --grid=output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/HN_limits/crab_final_hybridNew_limits_13_slices_envelope_3_func_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"/results/limits_13_slices_envelope_3_func_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"_merged.root -m 125 --cminDefaultMinimizerStrategy=0 --plot=limit_scan_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"_observed.pdf -n limits_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi" --rAbsAcc 0.00001; 

                combine output/Wide_Resonances_Run2_Final/datacards_alpha0p"$alphap"_refxsec0p01pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt -M HybridNew --LHCmode LHC-limits --readHybridResults --grid=output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/HN_limits/crab_final_hybridNew_limits_13_slices_envelope_3_func_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"/results/limits_13_slices_envelope_3_func_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"_merged.root -m 125 --cminDefaultMinimizerStrategy=0 --plot=limit_scan_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"_median_expected.pdf --expectedFromGrid 0.5 -n limits_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi" --rAbsAcc 0.00001; 

                combine output/Wide_Resonances_Run2_Final/datacards_alpha0p"$alphap"_refxsec0p01pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt -M HybridNew --LHCmode LHC-limits --readHybridResults --grid=output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/HN_limits/crab_final_hybridNew_limits_13_slices_envelope_3_func_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"/results/limits_13_slices_envelope_3_func_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"_merged.root -m 125 --cminDefaultMinimizerStrategy=0 --plot=limit_scan_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"_expected_minus_one_sigma.pdf --expectedFromGrid 0.16 -n limits_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi" --rAbsAcc 0.00001; 

                combine output/Wide_Resonances_Run2_Final/datacards_alpha0p"$alphap"_refxsec0p01pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt -M HybridNew --LHCmode LHC-limits --readHybridResults --grid=output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/HN_limits/crab_final_hybridNew_limits_13_slices_envelope_3_func_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"/results/limits_13_slices_envelope_3_func_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"_merged.root -m 125 --cminDefaultMinimizerStrategy=0 --plot=limit_scan_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"_expected_plus_one_sigma.pdf --expectedFromGrid 0.84 -n limits_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi" --rAbsAcc 0.00001; 

                combine output/Wide_Resonances_Run2_Final/datacards_alpha0p"$alphap"_refxsec0p01pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt -M HybridNew4J --LHCmode LHC-limits --readHybridResults --grid=output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/HN_limits/crab_final_hybridNew_limits_13_slices_envelope_3_func_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"/results/limits_13_slices_envelope_3_func_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"_merged.root -m 125 --cminDefaultMinimizerStrategy=0 --plot=limit_scan_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"_expected_minus_two_sigma.pdf --expectedFromGrid 0.025 -n limits_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi" --rAbsAcc 0.00001 --n4J 20 --stepsize4J "$stepsize" --option4J 3;                        

                combine output/Wide_Resonances_Run2_Final/datacards_alpha0p"$alphap"_refxsec0p01pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt -M HybridNew --LHCmode LHC-limits --readHybridResults --grid=output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/HN_limits/crab_final_hybridNew_limits_13_slices_envelope_3_func_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"/results/limits_13_slices_envelope_3_func_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"_merged.root -m 125 --cminDefaultMinimizerStrategy=0 --plot=limit_scan_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"_expected_plus_two_sigma.pdf --expectedFromGrid 0.975 -n limits_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi" --rAbsAcc 0.00001; 

                hadd higgsCombine_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi".HybridNew.mH120.root higgsCombinelimits_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi".HybridNew4J.mH125.quant0.025.root higgsCombinelimits_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi".HybridNew.mH125.quant0.160.root higgsCombinelimits_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi".HybridNew.mH125.quant0.500.root higgsCombinelimits_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi".HybridNew.mH125.quant0.840.root higgsCombinelimits_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi".HybridNew.mH125.quant0.975.root higgsCombinelimits_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi".HybridNew.mH125.root;  
 
                mv higgsCombine_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi".HybridNew.mH120.root output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/HN_limits/;
                mv higgsCombinelimits_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi".HybridNew*.root output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/HN_limits/;
                mv limit_scan_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"*.pdf output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/HN_limits/;
            exec bash "    
 
        done    
    done
done    
        
