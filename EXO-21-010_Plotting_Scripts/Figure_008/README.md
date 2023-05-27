.x plot_individual_canvases.C (run 13 times for each sub-canvas)

Inputs: test_pulls_alpha*.root (*=1,..,13)

Output: pad*_margin_V3.root (*=2,...,14)

.x plot_info_panel.C

Inputs: -

Output: pad1_margin_V3_PAS.root or pad1_margin_V3_PAPER.root

.x Plot_AllPulls.C

Inputs: pad1_margin_V3_PAS.root or pad1_margin_V3_PAPER.root, padX_margin_V3_PAS.root (X=2,...,14)

Output: Figure_008.pdf

