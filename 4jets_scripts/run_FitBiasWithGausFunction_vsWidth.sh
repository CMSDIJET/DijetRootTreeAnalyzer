
Suu_masses=(2000 2200 3000 4000 5000 6000 7000 8000 8600 9000 10000)
functions=(0 1 2)
injected_signals=(0 2 5)
alpha_true_values=(0.25)

for element1 in "${alpha_true_values[@]}"
do
    for element2 in "${functions[@]}"
    do
        for element3 in "${injected_signals[@]}"
        do
            for element4 in "${Suu_masses[@]}"
   	    do

                alpha_true=$element1
      	        function=$element2
      	        injected_signal=$element3
      	        Suu_mass=$element4
      	        
      	        
   	        root -l -q -b "FitBiasWithGausFunction_vsWidth.C($alpha_true, $Suu_mass, $function, $injected_signal)"
   	    
            
            done
       done   
    done
done    
