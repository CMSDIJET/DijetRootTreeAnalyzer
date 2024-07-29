
#widths=('0p0043' '0p015' '0p05' '0p1')
#Suu_masses=(2000 2200 3000 4000 5000 6000 7000 8000 8600 9000 10000)
#alpha_true_values=(0.25)

widths=('0p1')
Suu_masses=(3000)
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
                width_num=0.43
            elif [ "$width" == '0p015' ]; then
                width_num=1.5
            elif [ "$width" == '0p05' ]; then
                width_num=5
            elif [ "$width" == '0p1' ]; then
                width_num=10
   	    else
                echo "Unknown width: $width"
                continue
            fi       
            
             
  
	    #combine -M GoodnessOfFit --algo=saturated output/Wide_Resonances_Run2_Final/datacards_alpha0p"$alphap"_refxsec0p01pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt -n _SignalPlusBkgFit_W-"$width"_"$Suu"_"$Chi"_DATA
	    
	    #mv higgsCombine_SignalPlusBkgFit_W-"$width"_"$Suu"_"$Chi"_DATA.GoodnessOfFit.mH120.root output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/gofs/
	    
	    #combineTool.py -M GoodnessOfFit --algo=saturated -d output/Wide_Resonances_Run2_Final/datacards_alpha0p"$alphap"_refxsec0p01pb/workspace_combined_W-"$width"_"$Suu"_"$Chi".root -t 500 -s 123456:123655:1 --toysFrequentist -n _SignalPlusBkgFit_W-"$width"_"$Suu"_"$Chi"_TOYS --job-mode crab3 --task-name SignalPlusBkgFit_W-"$width"_"$Suu"_"$Chi"_TOYS --custom-crab custom_crab_GOF.py

            crab getoutput output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/gofs/crab_SignalPlusBkgFit_W-"$width"_"$Suu"_"$Chi"_TOYS/
            
            cd output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/gofs/crab_SignalPlusBkgFit_W-"$width"_"$Suu"_"$Chi"_TOYS/results/
            
            for f in *.tar; do tar xf $f; done
            
            hadd higgsCombine_SignalPlusBkgFit_W-"$width"_"$Suu"_"$Chi"_TOYS.GoodnessOfFit.mH120.root *.root
            
            cp higgsCombine_SignalPlusBkgFit_W-"$width"_"$Suu"_"$Chi"_TOYS.GoodnessOfFit.mH120.root ../../
            
            cd /eos/user/i/izisopou/4jets_Run2/CMSSW_14_1_0_pre4/src/CMSDIJET/DijetRootTreeAnalyzer/
            
            combineTool.py -M CollectGoodnessOfFit --input output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/gofs/higgsCombine_SignalPlusBkgFit_W-"$width"_"$Suu"_"$Chi"_DATA.GoodnessOfFit.mH120.root output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/gofs/higgsCombine_SignalPlusBkgFit_W-"$width"_"$Suu"_"$Chi"_TOYS.GoodnessOfFit.mH120.root -m 120.0 -o output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/gofs/gof_SignalPlusBkgFit_W-"$width"_"$Suu"_"$Chi".json
            
            python3 plotGof.py output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/gofs/gof_SignalPlusBkgFit_W-"$width"_"$Suu"_"$Chi".json --statistic saturated --mass 120.0 -o output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/gofs/gof_SignalPlusBkgFit_W-"$width"_"$Suu"_"$Chi" --title-right="Signal plus background fit" --cms-sub="Preliminary" --legend="#splitline{M_{S} = "$Suu" GeV}{#splitline{M_{#chi} = "$Chi" GeV}{#Gamma / M_{S} = "$width_num" %}}" --x-title="Saturated likelihood ratio" --y-title="Number of toys"

        done
	
   done   
done
