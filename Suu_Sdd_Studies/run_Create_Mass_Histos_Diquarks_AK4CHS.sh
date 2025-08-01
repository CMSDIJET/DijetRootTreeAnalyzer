#!/bin/bash

widths=(0.015 0.05 0.1)
Suu_masses=(2000 3000 4000 5000 6000 7000 8000 9000 10000)
alpha_true_values=(0.11 0.13 0.15 0.17 0.19 0.21 0.23 0.27 0.29 0.31 0.33 0.42)

for element1 in "${widths[@]}"
do
    for element2 in "${Suu_masses[@]}"
    do
        for element3 in "${alpha_true_values[@]}"
        do
    
        width=$element1
        Suu=$element2
        alpha_true=$element3             
        
        root -l -b -q "Create_Mass_Histos_Diquarks_AK4CHS.C($width, $alpha_true, $Suu)"

        done            
    done           
done

