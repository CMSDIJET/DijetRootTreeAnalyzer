#!/bin/bash

#./run_Create_Mass_Histos.sh

alpha_true_values=(0.11 0.13 0.15 0.17 0.19 0.21 0.23 0.27 0.29 0.31 0.33 0.42)
widths=(0.015 0.05 0.1)
Suu_masses=(2000 3000 4000 5000 6000 7000 8000 8400 8600 9000 10000 11000)

for element1 in "${alpha_true_values[@]}"
do
   for element2 in "${widths[@]}"
   do
      for element3 in "${Suu_masses[@]}"
      do

         alpha_true=$element1
         width=$element2
         Suu_mass=$element3

         if ( ([ "$Suu_mass" -eq 8400 ] || [ "$Suu_mass" -eq 8600 ]) && [ "$(echo "$alpha_true != 0.25" | bc)" -eq 1 ] )
         then
            continue
         fi


         for alphabin in {0..13}
         do
            #root -l -q -b -x "Create_Mass_Histos_Diquarks_AK4CHS_JESup.C($width,$alpha_true,$Suu_mass,$alphabin)"
            #root -l -q -b -x "Create_Mass_Histos_Diquarks_AK4CHS_JESdown.C($width,$alpha_true,$Suu_mass,$alphabin)"
            root -l -q -b -x "Create_Mass_Histos_Diquarks_AK4CHS_JERup.C($width,$alpha_true,$Suu_mass,$alphabin)"
         done


      done
   done
done

