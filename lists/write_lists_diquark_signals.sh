#!/bin/bash

Suu=(2000 3000 4000 5000 6000 7000 8000 9000 10000 11000)
alpha=(0.11 0.13 0.15 0.17 0.19 0.21 0.23 0.25 0.27 0.29 0.31 0.33 0.42)

for element1 in "${Suu[@]}"
do
   for element2 in "${alpha[@]}"
   do

      Suu=$element1
      Chi=$(echo "scale=0; ($element1*$element2)/1" | bc  ) 
      echo $Suu
      echo $Chi
      echo ""

      file_paths=(/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/big_trees/signal_diquarks/Run3Summer22EE/Suu_Diquark_S"$Suu"_chi"$Chi"_TuneCP2_13p6TeV_madgraph-pythia8/crab_Suu_Diquark_S"$Suu"_chi"$Chi"_TuneCP2_13p6TeV_madgraph-pythia8/*/0000/*)

      for file_path in "${file_paths[@]}"; do
          echo "$file_path" >> Suu_Diquark_signals/Run3Summer22EE/list_Run3Summer22EE_S"$Suu"_chi"$Chi".txt
      done

   done
done


Signals=(
   "2000 750"
   "2000 1000"
   "3000 500"
   "3000 1000"
   "4000 500"
   "4000 2000"
   "5000 1000"
   "5000 2000"
   "6000 1000"
   "6000 2000"
   "6000 2900"
   "7800 2100"
   "8000 1000"
   "8000 3000"
   "8100 2100"
   "8400 1900"
   "8400 2000"
   "8400 2100"
   "8400 2200"
   "8400 2300"
   "8600 2150"
   "8700 2100"
   "9000 2100"
)

for Signal in "${Signals[@]}"; do
   read -r Suu Chi <<< "$Signal"
   echo $Suu
   echo $Chi
   echo ""

   file_paths=(/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/big_trees/signal_diquarks/Run3Summer22EE/Suu_Diquark_S"$Suu"_chi"$Chi"_TuneCP2_13p6TeV_madgraph-pythia8/crab_Suu_Diquark_S"$Suu"_chi"$Chi"_TuneCP2_13p6TeV_madgraph-pythia8/*/0000/*)

   for file_path in "${file_paths[@]}"; do
       echo "$file_path" >> Suu_Diquark_signals/Run3Summer22EE/list_Run3Summer22EE_S"$Suu"_chi"$Chi".txt
   done

done



