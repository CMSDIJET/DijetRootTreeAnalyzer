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

void Plot_3_Mass_Spectra_for3p6TeVsignal(){

//TFile *f = new TFile("files/Information_panel_3p6TeV_PAS.root","READ");
TFile *f = new TFile("files/Information_panel_3p6TeV_PAPER.root","READ");
TFile *f_alpha9 = new TFile("files/Mass_spectrum_alphabin9_3p6TeV_obslim.root","READ");
TFile *f_alpha10 = new TFile("files/Mass_spectrum_alphabin10_3p6TeV_obslim.root","READ");
TFile *f_alpha11 = new TFile("files/Mass_spectrum_alphabin11_3p6TeV_obslim.root","READ");

TCanvas *c_info_panel = (TCanvas*)f->Get("panel");
TCanvas *c_alpha9 = (TCanvas*)f_alpha9->Get("c1");
TCanvas *c_alpha10 = (TCanvas*)f_alpha10->Get("c1");
TCanvas *c_alpha11 = (TCanvas*)f_alpha11->Get("c1");

TLegend *leg_alpha9 = new TLegend(0.31,0.88,0.71,0.98);
leg_alpha9->SetTextFont(42);
leg_alpha9->SetFillColorAlpha(0,0);
leg_alpha9->SetLineColor(0);
leg_alpha9->SetHeader("0.26 < #alpha < 0.28");
leg_alpha9->SetTextSize(0.072);

TLegend *leg_alpha10 = new TLegend(0.245,0.88,0.645,0.98);
leg_alpha10->SetTextFont(42);
leg_alpha10->SetFillColorAlpha(0,0);
leg_alpha10->SetLineColor(0);
leg_alpha10->SetHeader("0.28 < #alpha < 0.30");
leg_alpha10->SetTextSize(0.079);

TLegend *leg_alpha11 = new TLegend(0.233,0.88,0.633,0.98);
leg_alpha11->SetTextFont(42);
leg_alpha11->SetFillColorAlpha(0,0);
leg_alpha11->SetLineColor(0);
leg_alpha11->SetHeader("0.30 < #alpha < 0.32");
leg_alpha11->SetTextSize(0.076);

TCanvas *canvas = new TCanvas("canvas","",1500,1000);	

gStyle->SetLineScalePS(1);

TPad *info_panel = new TPad("info_panel", "info_panel", 0.098, 0.697, 0.962, 0.97);
TPad *Xaxis_panel = new TPad("Xaxis_panel", "Xaxis_panel", 0.05, 0, 1, 0.07);
TPad *Yaxis_panel = new TPad("Yaxis_panel", "Yaxis_panel", 0, 0, 0.075, 0.9);

TPad *pad_alpha9 = new TPad("pad_alpha9","pad_alpha9",0.075,0.07,0.382,0.7);
TPad *pad_alpha10 = new TPad("pad_alpha10","pad_alpha10",0.382,0.07,0.659,0.7);
TPad *pad_alpha11 = new TPad("pad_alpha11","pad_alpha11",0.659,0.07,0.95,0.7);

info_panel->Draw();
Xaxis_panel->Draw();
Yaxis_panel->Draw();

pad_alpha9->Draw();
pad_alpha10->Draw();
pad_alpha11->Draw();

info_panel->cd();
c_info_panel->DrawClonePad();

pad_alpha9->cd();
c_alpha9->DrawClonePad();
leg_alpha9->Draw();

pad_alpha10->cd();
c_alpha10->DrawClonePad();
leg_alpha10->Draw();

pad_alpha11->cd();
c_alpha11->DrawClonePad();
leg_alpha11->Draw();


Xaxis_panel->cd();

TLatex *x = new TLatex(0.6615, 0.4, "#font[42]{Four-jet mass [TeV]}");
x->SetTextSize(0.7);

x->Draw();


Yaxis_panel->cd();

TLatex *y1 = new TLatex(0.652, 0.47, "#font[42]{d#sigma/dm_{4j} [pb/TeV]}");
y1->SetTextSize(0.35);
y1->SetTextAngle(90);

y1->Draw();

TLatex *y2 = new TLatex(0.65, 0.135, "#font[42]{#frac{Data #minus Fit}{Uncertainty}}");
y2->SetTextSize(0.3);
y2->SetTextAngle(90);

y2->Draw();

canvas->SaveAs("plots/Figure_006.pdf");

}

