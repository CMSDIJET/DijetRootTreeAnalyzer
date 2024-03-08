#!/bin/bash

#example: ./open_screens_diquark_fullgrid.sh 

width='0p1'
#Suu_masses=(2000 3000 4000 5000 6000)
#Suu_masses=(7000 8000 8400 8600 9000 10000 11000)
Suu_masses=(5000)
#alpha_true_values=(0.11 0.13 0.15 0.17 0.19 0.21 0.23 0.25 0.27 0.29 0.31 0.33 0.42)
alpha_true_values=(0.17)

for element1 in "${Suu_masses[@]}"
do
   for element2 in "${alpha_true_values[@]}"
   do

      Suu=$element1
      alpha=$element2
      Chi=$(echo "scale=0; ($Suu*$alpha)/1" | bc  ) 
      
      if ( ([ "$Suu" -eq 8400 ] || [ "$Suu" -eq 8600 ]) && [ "$(echo "$alpha != 0.25" | bc)" -eq 1 ] )
      then
         continue
      fi
      
      echo $Suu
      echo $Chi

      screen -S list_Suu_Diquark_W-"$width"_S"$Suu"_chi"$Chi" -dm bash -c "sleep 5; cmsenv; source runjob_diquark_fullgrid.sh $width $Suu $Chi; exec bash"
   done
done



