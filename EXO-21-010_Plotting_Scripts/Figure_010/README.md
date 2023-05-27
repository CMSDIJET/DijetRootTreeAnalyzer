Produce the individual 12 canvases:

python Plot1DLimit_for_HybridNew_final_smoothing_CCLE.py -d limits/Limits_alpha0pXX/ -m gg -b PFDijet2017 -l 138 --massMin 2000 --massMax 9000  --xsecMin 1e-5 --xsecMax 0.09 --alpha_true 0.XX

tweaking each time the margin of the canvases based on where the canvas is located in the plot.

Produce the canvas for the information panel as well:

python Plot1DLimit_for_HybridNew_final_smoothing_CCLE_panel.py -d limits/Limits_alpha0pXX/ -m gg -b PFDijet2017 -l 138 --massMin 2000 --massMax 9000  --xsecMin 1e-5 --xsecMax 0.09 --alpha_true 0.XX

Create the final plot with all the canvases stitched together in one big canvas:

.x Plot_All_Limits.C

Inputs: limits/Limits_alpha0pXX/limits_freq_gg_pfdijet2017_alpha0pXX.root 

Output: Figure_010.pdf
