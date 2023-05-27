#include "TH2F.h"
#include "TH3I.h"
#include "TTree.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include "TMath.h"
#include "TLatex.h"
#include "TGraph.h"
#include "TLatex.h"

void Plot_All_3_Mass_Spectra(){

//TFile *f = new TFile("Mass_spectrum_panel_canvas_PAS.root","READ"); //for PAS - ilias
TFile *f = new TFile("Mass_spectrum_panel_canvas_PAPER.root","READ"); //for PAPER - ilias
TFile *f_alpha7 = new TFile("Mass_spectrum_alpha7_canvas_FR_v2.root","READ");
TFile *f_alpha8 = new TFile("Mass_spectrum_alpha8_canvas_FR_v2.root","READ");
TFile *f_alpha9 = new TFile("Mass_spectrum_alpha9_canvas_FR_v2.root","READ");

TCanvas *c_info_panel = (TCanvas*)f->Get("panel");
TCanvas *c_alpha7 = (TCanvas*)f_alpha7->Get("c1");
TCanvas *c_alpha8 = (TCanvas*)f_alpha8->Get("c1");
TCanvas *c_alpha9 = (TCanvas*)f_alpha9->Get("c1");

TLegend *leg_alpha7 = new TLegend(0.31,0.88,0.71,0.98);
leg_alpha7->SetTextFont(42);
leg_alpha7->SetFillColorAlpha(0,0);
leg_alpha7->SetLineColor(0);
leg_alpha7->SetHeader("0.22 < #alpha < 0.24");
leg_alpha7->SetTextSize(0.072);

TLegend *leg_alpha8 = new TLegend(0.245,0.88,0.645,0.98);
leg_alpha8->SetTextFont(42);
leg_alpha8->SetFillColorAlpha(0,0);
leg_alpha8->SetLineColor(0);
leg_alpha8->SetHeader("0.24 < #alpha < 0.26");
leg_alpha8->SetTextSize(0.079);

TLegend *leg_alpha9 = new TLegend(0.233,0.88,0.633,0.98);
leg_alpha9->SetTextFont(42);
leg_alpha9->SetFillColorAlpha(0,0);
leg_alpha9->SetLineColor(0);
leg_alpha9->SetHeader("0.26 < #alpha < 0.28");
leg_alpha9->SetTextSize(0.076);

TCanvas *canvas = new TCanvas("canvas","",1500,1000);	

gStyle->SetLineScalePS(1);

TPad *info_panel = new TPad("info_panel", "info_panel", 0.098, 0.697, 0.962, 0.97);
TPad *Xaxis_panel = new TPad("Xaxis_panel", "Xaxis_panel", 0.05, 0, 1, 0.07);
TPad *Yaxis_panel = new TPad("Yaxis_panel", "Yaxis_panel", 0, 0, 0.075, 0.9);

TPad *pad_alpha7 = new TPad("pad_alpha7","pad_alpha7",0.075,0.07,0.382,0.7);
TPad *pad_alpha8 = new TPad("pad_alpha8","pad_alpha8",0.382,0.07,0.659,0.7);
TPad *pad_alpha9 = new TPad("pad_alpha9","pad_alpha9",0.659,0.07,0.95,0.7);

info_panel->Draw();
Xaxis_panel->Draw();
Yaxis_panel->Draw();

pad_alpha7->Draw();
pad_alpha8->Draw();
pad_alpha9->Draw();

info_panel->cd();
c_info_panel->DrawClonePad();

pad_alpha7->cd();
c_alpha7->DrawClonePad();
leg_alpha7->Draw();

pad_alpha8->cd();
c_alpha8->DrawClonePad();
leg_alpha8->Draw();

pad_alpha9->cd();
c_alpha9->DrawClonePad();
leg_alpha9->Draw();


Xaxis_panel->cd();

TLatex *x = new TLatex(0.667, 0.4, "#font[42]{Four-jet mass [TeV]}");
x->SetTextSize(0.7);

x->Draw();


Yaxis_panel->cd();

TLatex *y1 = new TLatex(0.65, 0.43, "#font[42]{d#sigma/dm_{4j} [pb/TeV]}");
y1->SetTextSize(0.4);
y1->SetTextAngle(90);

y1->Draw();

TLatex *y2 = new TLatex(0.65, 0.15, "#font[42]{#frac{(Data-Fit)}{Uncertainty}}");
y2->SetTextSize(0.3);
y2->SetTextAngle(90);

y2->Draw();


canvas->SaveAs("Figure_007.pdf");

}

