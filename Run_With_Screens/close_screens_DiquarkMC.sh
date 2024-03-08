#!/bin/bash

#example: ./open_screens_QCDMC.sh 

Suu=(2000 3000 4000 5000 6000 7000 8000 9000 10000 11000)
alpha=(0.11 0.13 0.15 0.17 0.19 0.21 0.23 0.25 0.27 0.29 0.31 0.33 0.42)

for element1 in "${Suu[@]}"
do
   for element2 in "${alpha[@]}"
   do

      Suu=$element1
      Chi=$(echo "scale=0; ($element1*$element2)/1" | bc  ) 

      screen -X -S list_Suu_Diquark_S"$Suu"_chi"$Chi" quit
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

      screen -X -S list_Suu_Diquark_S"$Suu"_chi"$Chi" quit
done
