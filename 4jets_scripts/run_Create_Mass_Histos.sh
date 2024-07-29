#!/bin/bash

#./run_Create_Mass_Histos.sh

#alpha_true_values=(0.11 0.13 0.15 0.17 0.19 0.21 0.23 0.27 0.29 0.31 0.33 0.42)
alpha_true_values=(0.25)
widths=(0.015 0.05 0.1)
#widths=(0.0043)
#Suu_masses=(2000 3000 4000 5000 6000 7000 8000 8400 8600 9000 10000 11000)
Suu_masses=(8400)

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

         root -l -q -b -x "Create_Mass_Histos_Diquarks_AK4CHS.C($width,$alpha_true,$Suu_mass,0)"

         for alphabin in {1..13}
         do
            root -l -q -b -x "Create_Mass_Histos_Diquarks_AK4CHS.C($width,$alpha_true,$Suu_mass,$alphabin)"
         done


      done
   done
done

