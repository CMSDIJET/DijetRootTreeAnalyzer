
widths=('0p015' '0p05' '0p1')
#Suu_masses=(4500 4600 4700 4800 4900 5000 5100 5200 5300 5400 5500 5600 5700 5800 5900 6000 6100 6200 6300 6400 6500 6600 6700 6800 6900 7000 7100 7200 7300 7400 7500 7600 7700 7800 7900 8000 8100 8200 8300 8400 8500 8600 8700 8800 8900 9000 9100 9200 9300 9400 9500 9600 9700 9800 9900 10000)
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
   	    
   	    #if [[ "$width" == "0p015" && "$Suu" == 4900 ]]; then
            #    continue
            #fi

            #cd $CMSSW_BASE/src/CMSDIJET/DijetRootTreeAnalyzer/output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/HN_limits/crab_final_hybridNew_limits_13_slices_envelope_3_func_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"/results/     
            #for f in *.tar; do tar xf $f; done      
            #hadd limits_13_slices_envelope_3_func_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"_merged.root `ls higgsCombine.Test.POINT.*.HybridNew.mH125.*`
            
            cd $CMSSW_BASE/src/CMSDIJET/DijetRootTreeAnalyzer/output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/HN_significances/crab_final_hybridNew_significances_13_slices_envelope_3_func_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"/results/     
            for f in *.tar; do tar xf $f; done      
            hadd significances_13_slices_envelope_3_func_alpha0p"$alphap"_W-"$width"_"$Suu"_"$Chi"_merged.root `ls higgsCombine.Test*.HybridNew.mH120.*`
            
       done
   done   
done

