You need to be under a CMSSW release and do cmsenv in order to execute the command (it also runs without cmsenv but the position of titles and legends changes a bit):

python Plot1DLimit_for_HybridNew_final_pvalue.py -d alpha0p25/ -m gg -b PFDijet2017 -l 138.0 --massMin 2000 --massMax 10000  --signif --alpha_true 0.25

Inputs: root files inside alpha0p25/ , Diquark_0p25.txt (not used anywhere but need to give it just to prevent the code from crashing) 

Output: Figure_014.pdf
