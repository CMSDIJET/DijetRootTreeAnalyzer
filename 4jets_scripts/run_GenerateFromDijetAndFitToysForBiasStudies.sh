#!/bin/bash

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
   			
   	    echo "Width = $width"
   	    echo "Suu = $Suu"
   	    echo "Chi = $Chi"

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
            
            echo "rmax = $rmax"
            
            signal_2sigma=$(root -l -b -q "get_expected_limit.C((char*)\"$width\", $Suu, $Chi)" | tail -n 1)                 
            signal_5sigma=$(echo "scale=6; $signal_2sigma * 2" | bc)
            
            echo "2sigma signal = $signal_2sigma"
            echo "5sigma signal = $signal_5sigma"


            #Generate with DIJET function using 3 different signal hypotheses (0, 2sigma, 5sigma)
                       
            #combine output/Wide_Resonances_Run2_Final/datacards_alpha0p"$alphap"_refxsec0p01pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt -M GenerateOnly -t 2000 --expectSignal 0 --saveToys -n _W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal0 --setParameters pdf_index=0 --freezeParameters pdf_index 
                       
            #combine output/Wide_Resonances_Run2_Final/datacards_alpha0p"$alphap"_refxsec0p01pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt -M GenerateOnly -t 2000 --expectSignal $signal_2sigma --saveToys -n _W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal2sigma --setParameters pdf_index=0 --freezeParameters pdf_index 

            #combine output/Wide_Resonances_Run2_Final/datacards_alpha0p"$alphap"_refxsec0p01pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt -M GenerateOnly -t 2000 --expectSignal $signal_5sigma --saveToys -n _W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal5sigma --setParameters pdf_index=0 --freezeParameters pdf_index  
            
            #mv higgsCombine_W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal0.GenerateOnly.mH120.123456.root output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/bias_studies/
            #mv higgsCombine_W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal2sigma.GenerateOnly.mH120.123456.root output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/bias_studies/
            #mv higgsCombine_W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal5sigma.GenerateOnly.mH120.123456.root output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/bias_studies/



            #Fit with envelope the 3 different signal hypotheses (0, 2sigma, 5sigma)
            
            mkdir condor_for_bias_studies/W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal0_FitEnvelope/
            
            combineTool.py output/Wide_Resonances_Run2_Final/datacards_alpha0p"$alphap"_refxsec0p01pb/workspace_combined_W-"$width"_"$Suu"_"$Chi".root -M FitDiagnostics --toysFile output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/bias_studies/higgsCombine_W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal0.GenerateOnly.mH120.123456.root -t 2000 --rMin 0 --rMax $rmax --ignoreCovWarning --cminDefaultMinimizerStrategy=0 -n _W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal0_FitEnvelope --job-mode condor --task-name for_bias_studies/W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal0_FitEnvelope/W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal0_FitEnvelope --sub-opts='+JobFlavour="testmatch"'

            mkdir condor_for_bias_studies/W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal2sigma_FitEnvelope/

            combineTool.py output/Wide_Resonances_Run2_Final/datacards_alpha0p"$alphap"_refxsec0p01pb/workspace_combined_W-"$width"_"$Suu"_"$Chi".root -M FitDiagnostics --toysFile output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/bias_studies/higgsCombine_W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal2sigma.GenerateOnly.mH120.123456.root -t 2000 --rMin 0 --rMax $rmax --ignoreCovWarning --cminDefaultMinimizerStrategy=0 -n _W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal2sigma_FitEnvelope --job-mode condor --task-name for_bias_studies/W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal2sigma_FitEnvelope/W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal2sigma_FitEnvelope --sub-opts='+JobFlavour="testmatch"'

            mkdir condor_for_bias_studies/W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal5sigma_FitEnvelope/

            combineTool.py output/Wide_Resonances_Run2_Final/datacards_alpha0p"$alphap"_refxsec0p01pb/workspace_combined_W-"$width"_"$Suu"_"$Chi".root -M FitDiagnostics --toysFile output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p"$alphap"/bias_studies/higgsCombine_W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal5sigma.GenerateOnly.mH120.123456.root -t 2000 --rMin 0 --rMax $rmax --ignoreCovWarning --cminDefaultMinimizerStrategy=0 -n _W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal5sigma_FitEnvelope --job-mode condor --task-name for_bias_studies/W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal5sigma_FitEnvelope/W-"$width"_"$Suu"_"$Chi"_GenDijet_InjSignal5sigma_FitEnvelope --sub-opts='+JobFlavour="testmatch"'
            

        done
    done
done    

