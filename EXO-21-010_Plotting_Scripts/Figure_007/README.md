.x Plot_Combined_v6_alpha*.C  (* = 7,8,9)

Inputs: HISTOS_4J_Alldata_SR_alphabin*.root (data), DijetFitResult_PFDijet2017_4J_alphabin*_*_test.root (fits with the 3 functions), QCD2017_Standardcuts_M4Jgt1p6_nobreak_alpha*.root (QCD MC), ResonanceShapes_Suu*_Chi*_SR_alphabin*.root (signal shapes) 

Output: Mass_spectrum_alpha*_canvas.root (3 canvases)

.x Plot_Combined_v6_panel.C

Inputs: HISTOS_4J_Alldata_SR_alphabin7.root (data), DijetFitResult_PFDijet2017_4J_alphabin7_*_test.root (fits with the 3 functions), QCD2017_Standardcuts_M4Jgt1p6_nobreak_alpha7.root (QCD MC), ResonanceShapes_Suu*_Chi*_SR_alphabin7.root (signal shapes) 

Output: Mass_spectrum_panel_canvas.root (1 canvas)

.x Plot_All_3_Mass_Spectra.C

Inputs: Mass_spectrum_alpha*_canvas.root, Mass_spectrum_panel_canvas.root

Output: Figure_007.pdf
