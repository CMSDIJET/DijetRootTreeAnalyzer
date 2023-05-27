#include "TF1.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2D.h"
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

void Plot_All_Limits(){

//TFile *f = new TFile("limits/Information_panel_PAS.root","READ"); //for PAS -ilias
TFile *f = new TFile("limits/Information_panel_PAPER_FR.root","READ"); //for PAPER -ilias
TFile *f_0p11 = new TFile("limits/Limits_alpha0p11/limits_freq_gg_pfdijet2017_alpha0p11_FR.root","READ");
TFile *f_0p13 = new TFile("limits/Limits_alpha0p13/limits_freq_gg_pfdijet2017_alpha0p13_FR.root","READ");
TFile *f_0p15 = new TFile("limits/Limits_alpha0p15/limits_freq_gg_pfdijet2017_alpha0p15_FR.root","READ");
TFile *f_0p17 = new TFile("limits/Limits_alpha0p17/limits_freq_gg_pfdijet2017_alpha0p17_FR.root","READ");
TFile *f_0p19 = new TFile("limits/Limits_alpha0p19/limits_freq_gg_pfdijet2017_alpha0p19_FR.root","READ");
TFile *f_0p21 = new TFile("limits/Limits_alpha0p21/limits_freq_gg_pfdijet2017_alpha0p21_FR.root","READ");
TFile *f_0p23 = new TFile("limits/Limits_alpha0p23/limits_freq_gg_pfdijet2017_alpha0p23_FR.root","READ");
TFile *f_0p27 = new TFile("limits/Limits_alpha0p27/limits_freq_gg_pfdijet2017_alpha0p27_FR.root","READ");
TFile *f_0p29 = new TFile("limits/Limits_alpha0p29/limits_freq_gg_pfdijet2017_alpha0p29_FR.root","READ");
TFile *f_0p31 = new TFile("limits/Limits_alpha0p31/limits_freq_gg_pfdijet2017_alpha0p31_FR.root","READ");
TFile *f_0p33 = new TFile("limits/Limits_alpha0p33/limits_freq_gg_pfdijet2017_alpha0p33_FR.root","READ");
TFile *f_0p42 = new TFile("limits/Limits_alpha0p42/limits_freq_gg_pfdijet2017_alpha0p42_FR.root","READ");

TCanvas *c_info_panel = (TCanvas*)f->Get("panel");
TCanvas *c_0p11 = (TCanvas*)f_0p11->Get("c");
TCanvas *c_0p13 = (TCanvas*)f_0p13->Get("c");
TCanvas *c_0p15 = (TCanvas*)f_0p15->Get("c");
TCanvas *c_0p17 = (TCanvas*)f_0p17->Get("c");
TCanvas *c_0p19 = (TCanvas*)f_0p19->Get("c");
TCanvas *c_0p21 = (TCanvas*)f_0p21->Get("c");
TCanvas *c_0p23 = (TCanvas*)f_0p23->Get("c");
TCanvas *c_0p27 = (TCanvas*)f_0p27->Get("c");
TCanvas *c_0p29 = (TCanvas*)f_0p29->Get("c");
TCanvas *c_0p31 = (TCanvas*)f_0p31->Get("c");
TCanvas *c_0p33 = (TCanvas*)f_0p33->Get("c");
TCanvas *c_0p42 = (TCanvas*)f_0p42->Get("c");

TLegend *leg_alpha_0p11 = new TLegend(0.505,0.85,0.905,0.95);
leg_alpha_0p11->SetTextFont(42);
leg_alpha_0p11->SetFillColorAlpha(0,0);
leg_alpha_0p11->SetLineColor(0);
leg_alpha_0p11->SetHeader("M(X) / M(Y) = 0.11");
leg_alpha_0p11->SetTextSize(0.072);

TLegend *leg_alpha_0p13 = new TLegend(0.50,0.85,0.90,0.95);
leg_alpha_0p13->SetTextFont(42);
leg_alpha_0p13->SetFillColorAlpha(0,0);
leg_alpha_0p13->SetLineColor(0);
leg_alpha_0p13->SetHeader("M(X) / M(Y) = 0.13");
leg_alpha_0p13->SetTextSize(0.07);

TLegend *leg_alpha_0p15 = new TLegend(0.50,0.85,0.90,0.95);
leg_alpha_0p15->SetTextFont(42);
leg_alpha_0p15->SetFillColorAlpha(0,0);
leg_alpha_0p15->SetLineColor(0);
leg_alpha_0p15->SetHeader("M(X) / M(Y) = 0.15");
leg_alpha_0p15->SetTextSize(0.07);

TLegend *leg_alpha_0p17 = new TLegend(0.505,0.85,0.905,0.95);
leg_alpha_0p17->SetTextFont(42);
leg_alpha_0p17->SetFillColorAlpha(0,0);
leg_alpha_0p17->SetLineColor(0);
leg_alpha_0p17->SetHeader("M(X) / M(Y) = 0.17");
leg_alpha_0p17->SetTextSize(0.068);

TLegend *leg_alpha_0p19 = new TLegend(0.435,0.85,0.835,0.95);
leg_alpha_0p19->SetTextFont(42);
leg_alpha_0p19->SetFillColorAlpha(0,0);
leg_alpha_0p19->SetLineColor(0);
leg_alpha_0p19->SetHeader("M(X) / M(Y) = 0.19");
leg_alpha_0p19->SetTextSize(0.072);

TLegend *leg_alpha_0p21 = new TLegend(0.442,0.85,0.842,0.95);
leg_alpha_0p21->SetTextFont(42);
leg_alpha_0p21->SetFillColorAlpha(0,0);
leg_alpha_0p21->SetLineColor(0);
leg_alpha_0p21->SetHeader("M(X) / M(Y) = 0.21");
leg_alpha_0p21->SetTextSize(0.07);

TLegend *leg_alpha_0p23 = new TLegend(0.442,0.85,0.842,0.95);
leg_alpha_0p23->SetTextFont(42);
leg_alpha_0p23->SetFillColorAlpha(0,0);
leg_alpha_0p23->SetLineColor(0);
leg_alpha_0p23->SetHeader("M(X) / M(Y) = 0.23");
leg_alpha_0p23->SetTextSize(0.07);

TLegend *leg_alpha_0p27 = new TLegend(0.44,0.85,0.84,0.95);
leg_alpha_0p27->SetTextFont(42);
leg_alpha_0p27->SetFillColorAlpha(0,0);
leg_alpha_0p27->SetLineColor(0);
leg_alpha_0p27->SetHeader("M(X) / M(Y) = 0.27");
leg_alpha_0p27->SetTextSize(0.068);

TLegend *leg_alpha_0p29 = new TLegend(0.43,0.85,0.83,0.95);
leg_alpha_0p29->SetTextFont(42);
leg_alpha_0p29->SetFillColorAlpha(0,0);
leg_alpha_0p29->SetLineColor(0);
leg_alpha_0p29->SetHeader("M(X) / M(Y) = 0.29");
leg_alpha_0p29->SetTextSize(0.072);

TLegend *leg_alpha_0p31 = new TLegend(0.433,0.85,0.833,0.95);
leg_alpha_0p31->SetTextFont(42);
leg_alpha_0p31->SetFillColorAlpha(0,0);
leg_alpha_0p31->SetLineColor(0);
leg_alpha_0p31->SetHeader("M(X) / M(Y) = 0.31");
leg_alpha_0p31->SetTextSize(0.07);

TLegend *leg_alpha_0p33 = new TLegend(0.435,0.85,0.835,0.95);
leg_alpha_0p33->SetTextFont(42);
leg_alpha_0p33->SetFillColorAlpha(0,0);
leg_alpha_0p33->SetLineColor(0);
leg_alpha_0p33->SetHeader("M(X) / M(Y) = 0.33");
leg_alpha_0p33->SetTextSize(0.07);

TLegend *leg_alpha_0p42 = new TLegend(0.43,0.85,0.83,0.95);
leg_alpha_0p42->SetTextFont(42);
leg_alpha_0p42->SetFillColorAlpha(0,0);
leg_alpha_0p42->SetLineColor(0);
leg_alpha_0p42->SetHeader("M(X) / M(Y) = 0.42");
leg_alpha_0p42->SetTextSize(0.068);

TCanvas *canvas = new TCanvas("canvas","",3000,4000);	

gStyle->SetLineScalePS(1);

//canvas->cd();

TPad *info_panel = new TPad("info_panel", "info_panel", 0.076, 0.86, 1, 0.99);
TPad *Xaxis_panel = new TPad("Xaxis_panel", "Xaxis_panel", 0.05, 0, 1, 0.047);
TPad *Yaxis_panel = new TPad("Yaxis_panel", "Yaxis_panel", 0, 0, 0.05, 0.9);

TPad *pad_0p11 = new TPad("pad_0p11","pad_0p11",0.045,0.665,0.38,0.862);
TPad *pad_0p19 = new TPad("pad_0p19","pad_0p19",0.38,0.665,0.675,0.862);
TPad *pad_0p29 = new TPad("pad_0p29","pad_0p29",0.675,0.665,0.977,0.862);

TPad *pad_0p13 = new TPad("pad_0p13","pad_0p13",0.045,0.4645,0.38,0.665);
TPad *pad_0p21 = new TPad("pad_0p21","pad_0p21",0.38,0.4645,0.675,0.665);
TPad *pad_0p31 = new TPad("pad_0p31","pad_0p31",0.675,0.4645,0.977,0.665);

TPad *pad_0p15 = new TPad("pad_0p15","pad_0p15",0.045,0.26,0.38,0.4645);
TPad *pad_0p23 = new TPad("pad_0p23","pad_0p23",0.38,0.26,0.675,0.4645);
TPad *pad_0p33 = new TPad("pad_0p33","pad_0p33",0.675,0.26,0.977,0.4645);

TPad *pad_0p17 = new TPad("pad_0p17","pad_0p15",0.045,0.046,0.38,0.26);
TPad *pad_0p27 = new TPad("pad_0p27","pad_0p23",0.38,0.046,0.675,0.26);
TPad *pad_0p42 = new TPad("pad_0p42","pad_0p33",0.675,0.046,0.977,0.26);

info_panel->Draw();
Xaxis_panel->Draw();
Yaxis_panel->Draw();

pad_0p11->Draw();
pad_0p19->Draw();
pad_0p29->Draw();

pad_0p13->Draw();
pad_0p21->Draw();
pad_0p31->Draw();

pad_0p15->Draw();
pad_0p23->Draw();
pad_0p33->Draw();

pad_0p17->Draw();
pad_0p27->Draw();
pad_0p42->Draw();

info_panel->cd();
c_info_panel->DrawClonePad();

pad_0p11->cd();
c_0p11->DrawClonePad();
leg_alpha_0p11->Draw();
pad_0p19->cd();
c_0p19->DrawClonePad();
leg_alpha_0p19->Draw();
pad_0p29->cd();
c_0p29->DrawClonePad();
leg_alpha_0p29->Draw();

pad_0p13->cd();
c_0p13->DrawClonePad();
leg_alpha_0p13->Draw();
pad_0p21->cd();
c_0p21->DrawClonePad();
leg_alpha_0p21->Draw();
pad_0p31->cd();
c_0p31->DrawClonePad();
leg_alpha_0p31->Draw();

pad_0p15->cd();
c_0p15->DrawClonePad();
leg_alpha_0p15->Draw();
pad_0p23->cd();
c_0p23->DrawClonePad();
leg_alpha_0p23->Draw();
pad_0p33->cd();
c_0p33->DrawClonePad();
leg_alpha_0p33->Draw();

pad_0p17->cd();
c_0p17->DrawClonePad();
leg_alpha_0p17->Draw();
pad_0p27->cd();
c_0p27->DrawClonePad();
leg_alpha_0p27->Draw();
pad_0p42->cd();
c_0p42->DrawClonePad();
leg_alpha_0p42->Draw();

Xaxis_panel->cd();

TLatex *x = new TLatex(0.47, 0.4, "#font[42]{Four-jet resonance mass [TeV]}");
x->SetTextSize(0.6);

x->Draw();


Yaxis_panel->cd();

TLatex *y = new TLatex(0.7, 0.733, "#font[42]{#sigma #times #Beta #times #Alpha [pb]}");
y->SetTextSize(0.9);
y->SetTextAngle(90);

y->Draw();

//TFile *output = new TFile("output.root","RECREATE"); 
//canvas->Write();

canvas->SaveAs("Figure_010.pdf");

}
