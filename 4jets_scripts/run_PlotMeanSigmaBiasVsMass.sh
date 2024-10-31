
functions=(0 1 2)
injected_signals=(2 5)
alpha_true_values=(0.25)

for element1 in "${alpha_true_values[@]}"
do
    for element2 in "${functions[@]}"
    do
        for element3 in "${injected_signals[@]}"
        do
            
            alpha_true=$element1
      	    function=$element2
      	    injected_signal=$element3
   	        
   	    root -l -q -b "PlotMeanBiasVsMass.C($alpha_true, $function, $injected_signal)"
   	    root -l -q -b "PlotSigmaBiasVsMass.C($alpha_true, $function, $injected_signal)"
   	    
       done   
    done
done    
