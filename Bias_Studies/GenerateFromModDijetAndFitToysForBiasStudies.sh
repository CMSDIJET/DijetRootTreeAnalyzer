#!/bin/bash

export SCRAM_ARCH=slc7_amd64_gcc700
source /afs/cern.ch/cms/cmsset_default.sh
eval `scramv1 runtime -sh`

# ./GenerateFromModDijetAndFitToysForBiasStudies.sh 8400 2100 0p0043 0.190423 3
# ./GenerateFromModDijetAndFitToysForBiasStudies.sh 8400 2100 0p015 0.209863 3.5
# ./GenerateFromModDijetAndFitToysForBiasStudies.sh 8400 2100 0p05 0.284180 4.5
# ./GenerateFromModDijetAndFitToysForBiasStudies.sh 8400 2100 0p1 0.325195 5

Suu=$1
Chi=$2
width=$3
signal_2sigma=$4
rmax=$5

alpha=$(echo "scale=2; $Chi / $Suu" | bc)
alphap=$(echo "$alpha * 100 / 1" | bc)

signal_5sigma=$(echo "scale=6; $signal_2sigma * 2" | bc)


echo "Suu mass = $Suu GeV"
echo "Chi mass = $Chi GeV"
echo "alpha = $alpha"
echo "alpha name = 0p$alphap"
echo "Diquark width name = $width"
echo "2 sigma signal = $signal_2sigma"
echo "5 sigma signal = $signal_5sigma"

#Generate with MODDIJET function using 3 different signal hypotheses (0, 2sigma, 5sigma)

combine output/Wide_Resonances_RunII_Initial_Request/datacards_alpha0p"$alphap"_refxsec0p0001pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt -M GenerateOnly -t 1000 --expectSignal 0 --saveToys -n _W-"$width"_"$Suu"_"$Chi"_GenModDijet_InjSignal0 --setParameters pdf_index=2 --freezeParameters pdf_index #--toysFrequentist 

combine output/Wide_Resonances_RunII_Initial_Request/datacards_alpha0p"$alphap"_refxsec0p0001pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt -M GenerateOnly -t 1000 --expectSignal $signal_2sigma --saveToys -n _W-"$width"_"$Suu"_"$Chi"_GenModDijet_InjSignal2sigma --setParameters pdf_index=2 --freezeParameters pdf_index #--toysFrequentist

combine output/Wide_Resonances_RunII_Initial_Request/datacards_alpha0p"$alphap"_refxsec0p0001pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt -M GenerateOnly -t 1000 --expectSignal $signal_5sigma --saveToys -n _W-"$width"_"$Suu"_"$Chi"_GenModDijet_InjSignal5sigma --setParameters pdf_index=2 --freezeParameters pdf_index #--toysFrequentist


#Fit with envelope the 3 different signal hypotheses (0, 2sigma, 5sigma)

combine output/Wide_Resonances_RunII_Initial_Request/datacards_alpha0p"$alphap"_refxsec0p0001pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt -M FitDiagnostics --toysFile higgsCombine_W-"$width"_"$Suu"_"$Chi"_GenModDijet_InjSignal0.GenerateOnly.mH120.123456.root -t 1000 --rMin 0 --rMax $rmax --ignoreCovWarning --cminDefaultMinimizerStrategy=0  -n _W-"$width"_"$Suu"_"$Chi"_GenModDijet_FitEnvelope_InjSignal0 #--saveToys

combine output/Wide_Resonances_RunII_Initial_Request/datacards_alpha0p"$alphap"_refxsec0p0001pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt -M FitDiagnostics --toysFile higgsCombine_W-"$width"_"$Suu"_"$Chi"_GenModDijet_InjSignal2sigma.GenerateOnly.mH120.123456.root -t 1000 --rMin 0 --rMax $rmax --ignoreCovWarning --cminDefaultMinimizerStrategy=0  -n _W-"$width"_"$Suu"_"$Chi"_GenModDijet_FitEnvelope_InjSignal2sigma #--saveToys

combine output/Wide_Resonances_RunII_Initial_Request/datacards_alpha0p"$alphap"_refxsec0p0001pb/card_combined_W-"$width"_"$Suu"_"$Chi".txt -M FitDiagnostics --toysFile higgsCombine_W-"$width"_"$Suu"_"$Chi"_GenModDijet_InjSignal5sigma.GenerateOnly.mH120.123456.root -t 1000 --rMin 0 --rMax $rmax --ignoreCovWarning --cminDefaultMinimizerStrategy=0  -n _W-"$width"_"$Suu"_"$Chi"_GenModDijet_FitEnvelope_InjSignal5sigma #--saveToys


#mv higgsCombine*.root Bias_Studies/rootfiles/
#mv fitDiagnostics*.root Bias_Studies/rootfiles/


